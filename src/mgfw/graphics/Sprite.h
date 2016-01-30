#pragma once

#include "..\graphics\Transformable.h"
#include "..\graphics\Drawable.h"
#include "..\graphics\VertexArray.h"

namespace mg {

class Sprite : public Transformable, public Drawable {
public:
    Sprite();

    void draw(Renderer& renderer, RenderStates states) const ;

    void setTexture(const Texture* texture);
    const Texture* getTexture() const;

private:
    VertexArray m_vertices;
    const Texture* m_texture;

};

} // namespace mg
