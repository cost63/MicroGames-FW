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
    m_vertices.clear();

    // ...

    m_needUpdate = false;
}

} // namespace mg
