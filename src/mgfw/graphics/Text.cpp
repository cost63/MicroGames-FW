#include "text.h"

#include "../graphics/Font.h"

namespace mg {

Text::Text()
: m_font(nullptr)
{}

void Text::setFont(const Font* font) {
    m_font = font;
}

const Font* Text::getFont() const {
    return m_font;
}

void Text::setString(const std::string& str) {
    m_string = str;
}

const std::string& Text::getString() const {
    return m_string;
}

void Text::setCharSize(uint16_t charSize) {
    m_charSize = charSize;
}

uint16_t Text::getCharSize() const {
    return m_charSize;
}

} // namespace mg
