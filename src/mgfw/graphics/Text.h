#pragma once

#include "../graphics/VertexArray.h"

namespace mg {

/* Forward declarations */
class Font;

class Text {
public:
    Text();

    void setFont(const Font* font);
    const Font* getFont() const;

private:
    void ensureUpdate() const;

private:
    const Font* m_font;

    VertexArray m_vertices;
};

} // namespace mg
