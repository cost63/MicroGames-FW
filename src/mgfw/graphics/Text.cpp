#include "text.h"

#include "../graphics/Font.h"

namespace mg {

Text::Text()
: m_font(nullptr)
, m_needUpdate(false)
{}

void Text::draw(Renderer& renderer, RenderStates states) const {
    if(m_needUpdate) {
        updateText();
    }

    // ...
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

/* Private */

void Text::updateText() const {
    // Clean up current state of text
    m_vertices.clear();

    // Offset between characters (x) and lines (y)
    Vec2f offset;

    // TODO(Smeky) Replace this by push_back in the loop as we can't support exact
    //             number of characters because of specials symbols and underline
    // Resize vertices to support all characters in the string
    m_vertices.resize(m_string.length() * 4);

    for(uint32_t i = 0; i < m_string.length(); i++) {
        // Store current character from the string
        const char current = m_string[i];

        // Get font glyph corresponding to the current character
        const Font::Glyph glyph = m_font->getGlyph(current, m_charSize);
        const iRect clip        = glyph.clip;

        Vertex& v0 = m_vertices[4 * i + 0];
        Vertex& v1 = m_vertices[4 * i + 1];
        Vertex& v2 = m_vertices[4 * i + 2];
        Vertex& v3 = m_vertices[4 * i + 3];

        // Set position of vertices
        v0.pos = offset;
        v1.pos = Vec2f(offset.x + clip.w, offset.y);
        v2.pos = offset + clip.size();
        v3.pos = Vec2f(offset.x, offset.y + clip.h);

        // Set glyph's texture clip
        v0.texCoord = clip.pos();
        v1.texCoord = clip.pos() + Vec2f(clip.w, 0);
        v2.texCoord = clip.pos() + clip.size();
        v3.texCoord = clip.pos() + Vec2f(0, clip.h);
    }

    m_needUpdate = false;
}

} // namespace mg
