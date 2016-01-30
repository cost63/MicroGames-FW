#include "Sprite.h"

#include "../graphics/Texture.h"

namespace mg {

Sprite::Sprite()
: m_texture(nullptr)
{
    // Setup default vertices
    m_vertices.resize(4);
    m_vertices.type = PrimitiveType::Quads;

    m_vertices[0].pos = Vec2f( 0,  0);
    m_vertices[1].pos = Vec2f( 1,  0);
    m_vertices[2].pos = Vec2f( 1,  1);
    m_vertices[3].pos = Vec2f( 0,  1);

    m_vertices[0].texCoord = Vec2f(0, 0);
    m_vertices[1].texCoord = Vec2f(1, 0);
    m_vertices[2].texCoord = Vec2f(1, 1);
    m_vertices[3].texCoord = Vec2f(0, 1);
}

void Sprite::draw(Renderer& renderer, RenderStates states) const {
    states.texture = m_texture;
    states.transform *= getMatrix();

    renderer.draw(m_vertices, states);
}

void Sprite::setTexture(const Texture* texture) {
    m_texture = texture;

    if(texture) {
        const Vec2u tSize = texture->getSize();
        setSize(tSize.x, tSize.y);
    }
}

const Texture* Sprite::getTexture() const {
    return m_texture;
}

} // namespace mg
