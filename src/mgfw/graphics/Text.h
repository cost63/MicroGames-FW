#pragma once

#include <string>

#include "../graphics/VertexArray.h"

namespace mg {

/* Forward declarations */
class Font;

class Text {
public:
    Text();

    void setString(const std::string& str);
    const std::string& getString() const;

    void setFont(const Font* font);
    const Font* getFont() const;

    void setCharSize(uint16_t size);
    uint16_t getCharSize() const;

private:
    void ensureUpdate() const;

private:
    const Font* m_font;

    std::string m_string;
    uint16_t m_charSize;

    mutable VertexArray m_vertices;
    mutable bool m_shouldUpdate;
};

} // namespace mg
