#pragma once

#include "../graphics/Transformable.h"
#include "../graphics/VertexArray.h"

namespace mg {

class Shape : public Transformable, public Drawable {
public:
    Shape();

    void draw(Renderer& renderer, RenderStates states) const;

    void setColor(const Color& color);
    Color getColor() const;

    void setTexture(const Texture* texure);
    const Texture* getTexture() const;

    VertexArray& getVertices();
    const VertexArray& getVertices() const;

protected:
    VertexArray m_vertices;

    Color m_color;
    const Texture* m_texture;
};

} // namespace mg
