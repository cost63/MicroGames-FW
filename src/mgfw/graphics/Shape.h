#pragma once

#include "../graphics/Transformable.h"
#include "../graphics/VertexArray.h"

namespace mg {

class Shape : public Transformable, public Drawable {
public:
    Shape();

    virtual void draw(Renderer& renderer, RenderStates states) const override;

    void setColor(const Color& color);
    void setColor(const Color& color, uint32_t index);
    Color getColor() const;

    void setTexture(const Texture* texure);
    const Texture* getTexture() const;

    void setUnitMode(UnitMode mode);
    UnitMode getUnitMode() const;

    VertexArray& getVertices();
    const VertexArray& getVertices() const;

protected:
    VertexArray m_vertices;

    Color m_color;
    const Texture* m_texture;
};

} // namespace mg
