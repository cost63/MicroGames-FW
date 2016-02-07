#include "text.h"

#include "../graphics/Font.h"

namespace mg {

Text::Text()
: m_font(nullptr)
, m_shouldUpdate(false)
{}

void Text::setString(const std::string& str) {
    if(m_string != str) {
        m_string = str;
        m_shouldUpdate = true;
    }
}

const std::string& Text::getString() const {
    return m_string;
}

void Text::setFont(const Font* font) {
    if(m_font != font) {
        m_font = font;
        m_shouldUpdate = true;
    }
}

const Font* Text::getFont() const {
    return m_font;
}

void Text::setCharSize(uint16_t size) {
    if(m_charSize != size) {
        m_charSize = size;
        m_shouldUpdate = true;
    }
}

uint16_t Text::getCharSize() const {
    return m_charSize;
}

/* Private */

void Text::ensureUpdate() const {
    m_vertices.clear();

    float horSpace = 0.0;
    float verSpace = 0.0;
//    float horSpace = (float)(m_font->getGlyph(L' ', m_charSize).advance);
//    float verSpace = (float)(m_font->getLineSpacing(m_charSize));
    float x = 0.0;
    float y = (float)m_charSize;

    float minX = (float)m_charSize;
    float minY = (float)m_charSize;
    float maxX = 0.0;
    float maxY = 0.0;

    uint32_t previousChar = 0;

    for(uint32_t i = 0; i < m_string.length(); i++) {
        const uint32_t currentChar = m_string[i];

//        x += m_font->getKerning(previousChar, currentChar, m_charSize);
        previousChar = currentChar;

        if(currentChar == ' ' || currentChar == '\t' || currentChar == '\n') {
            minX = std::min(minX, x);
            minX = std::min(minY, y);

            switch(currentChar) {
            case ' ':  x += horSpace; break;
            case '\t': x += horSpace * 4; break;
            case '\n': y += horSpace; x = 0.0; break;
            }

            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);
        }

//        // Get current glyph's description
//        const Glyph& glyph = m_font->getGlyph(currentChar, m_charSize);
//
//        // Add the glyph to the vertices
//        addGlyphQuad(m_vertices, Vec2f(x, y), glyph);
//
//        // Advance to the next character
//        x += glyph.advance;
    }
}

} // namespace mg
