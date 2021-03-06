#pragma once

#include <string>

#include "../graphics/Transformable.h"
#include "../graphics/Drawable.h"
#include "../graphics/VertexArray.h"

namespace mg {

/* Forward declarations */
class Font;

class Text : public Transformable, public Drawable {
public:
    enum Style {
        Bold,
        Italic,
    };

public:
    Text();

    void draw(Renderer& renderer, RenderStates states) const;

    void setFont(const Font* font);
    const Font* getFont() const;

    void setString(const std::string& str);
    const std::string& getString() const;

    void setCharSize(uint16_t charSize);
    uint16_t getCharSize() const;

    void enableStyle(Text::Style style);
    void disableStyle(Text::Style style);
    bool isStyleEnabled(Text::Style style) const;

private:
    void updateText() const;

private:
    const Font* m_font;

    std::string m_string;
    uint16_t m_charSize;

    bool m_bold;
    bool m_italic;

    mutable VertexArray m_vertices;
    mutable bool m_needUpdate;
};

} // namespace mg
