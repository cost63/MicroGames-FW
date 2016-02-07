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

/* Private */

void Text::ensureUpdate() const {

}

} // namespace mg
