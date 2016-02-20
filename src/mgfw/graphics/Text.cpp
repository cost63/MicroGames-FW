#include "text.h"

#include "../graphics/Font.h"

namespace mg {

Text::Text()
: m_font(nullptr)
, m_charSize(11)
, m_bold(false)
, m_italic(false)
, m_needUpdate(false)
{
    m_vertices.type = PrimitiveType::Quads;
}

void Text::draw(Renderer& renderer, RenderStates states) const {
    if(!m_font) {
        return;
    }

    if(m_needUpdate) {
        updateText();
    }

    states.texture = m_font->getTexture(m_charSize);
    states.transform *= getMatrix();

    renderer.draw(m_vertices, states);
}

void Text::setFont(const Font* font) {
    m_font = font;
    m_needUpdate = true;
}

const Font* Text::getFont() const {
    return m_font;
}

void Text::setString(const std::string& str) {
    m_string = str;
    m_needUpdate = true;
}

const std::string& Text::getString() const {
    return m_string;
}

void Text::setCharSize(uint16_t charSize) {
    m_charSize = charSize;
    m_needUpdate = true;
}

uint16_t Text::getCharSize() const {
    return m_charSize;
}

void Text::setBoldStyle(bool enabled) {
    m_bold = enabled;
}

bool Text::isBoldStyle() const {
    return m_bold;
}

void Text::setItalicStyle(bool enabled) {
    m_italic = enabled;
}

bool Text::isItalicStyle() const {
    return m_italic;
}

/* Private */

void Text::updateText() const {
    // Clean up current state of text
    m_vertices.clear();

    // Offset between characters (x) and lines (y)
    Vec2f offset;

    // TODO(Smeky) Replace this by push_back in the loop as we can't support exact
    //             number of characters because of specials symbols and underline
    // Resize vertices to support all characters in the string
//    m_vertices.resize(m_string.length() * 4);

    for(uint32_t i = 0; i < m_string.length(); i++) {
        // Store current character from the string
        const char current = m_string[i];

        // Get font glyph corresponding to the current character
        const Font::Glyph glyph = m_font->getGlyph(current, m_charSize, m_bold);
        const iRect clip        = glyph.clip;

        // Line breaking
        if(current == '\n') {
            offset.x  = 0.0;
            offset.y += glyph.clip.h;

            continue;
        }
        else if(current == ' ') {
            offset.x += glyph.clip.w;

            continue;
        }

        Vertex v0;
        Vertex v1;
        Vertex v2;
        Vertex v3;

        // Set position of vertices
        v0.pos = offset;
        v1.pos = Vec2f(offset.x + clip.w, offset.y);
        v2.pos = offset + clip.size();
        v3.pos = Vec2f(offset.x, offset.y + clip.h);

        if(m_italic) {
            v0.pos.x += glyph.clip.h * 0.208;
            v1.pos.x += glyph.clip.h * 0.208;
        }

        // Calculate normalized clip dimensions
        const Vec2u& texSize = m_font->getTexture(m_charSize)->getSize();
        const Vec2f& cPos    = Vec2f(clip.pos()) / texSize;
        const Vec2f& cSize   = Vec2f(clip.size()) / texSize;

        // Set glyph's texture clip
        v0.texCoord = cPos;
        v1.texCoord = cPos + Vec2f(cSize.w, 0);
        v2.texCoord = cPos + cSize;
        v3.texCoord = cPos + Vec2f(0, cSize.h);

        m_vertices.push_back(v0);
        m_vertices.push_back(v1);
        m_vertices.push_back(v2);
        m_vertices.push_back(v3);

        offset.x += clip.w;
    }

    m_needUpdate = false;
}

} // namespace mg
