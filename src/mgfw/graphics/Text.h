#pragma once

namespace mg {

/* Forward declarations */
class Font;

class Text {
public:
    Text();

    void setFont(const Font* font);
    const Font* getFont() const;

private:
    const Font* m_font;

};

} // namespace mg
