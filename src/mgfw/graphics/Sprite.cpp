#include "Sprite.h"

#include "../graphics/Texture.h"

namespace mg {

Sprite::Sprite()
: m_texture(nullptr)
, m_isClipSet(false)
{
    // Setup default vertices
    m_vertices.resize(4);
    m_vertices.type = PrimitiveType::Quads;

//    m_vertices[0].pos = Vec2f( 0,  0);
//    m_vertices[1].pos = Vec2f( 1,  0);
//    m_vertices[2].pos = Vec2f( 1,  1);
//    m_vertices[3].pos = Vec2f( 0,  1);
//
//    m_vertices[0].texCoord = Vec2f(0, 0);
//    m_vertices[1].texCoord = Vec2f(1, 0);
//    m_vertices[2].texCoord = Vec2f(1, 1);
//    m_vertices[3].texCoord = Vec2f(0, 1);
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
        setSize(tSize);

        if(!m_isClipSet) {
            m_clip.x = 0;
            m_clip.y = 0;
            m_clip.w = tSize.w;
            m_clip.h = tSize.h;
        }

        updateClipVertices();
    }
}

const Texture* Sprite::getTexture() const {
    return m_texture;
}

void Sprite::setClip(const iRect& clip) {
    m_clip = clip;

    updateClipVertices();

    m_isClipSet = true;
}

void Sprite::setClip(int x, int y, int w, int h) {
    setClip(iRect(x, y, w, h));
}

iRect Sprite::getClip() const {
    return m_clip;
}

/* Private */

void Sprite::updateClipVertices() {
    if(m_texture) {
        const Vec2u tSize = m_texture->getSize();

        Vec2f cPos(Vec2f(m_clip.pos()) / tSize);
        Vec2f cSize(Vec2f(m_clip.size()) / tSize);

        m_vertices[0].texCoord = cPos;
        m_vertices[1].texCoord = Vec2f( cPos.x + cSize.w, cPos.y );
        m_vertices[2].texCoord = Vec2f( cPos.x + cSize.w, cPos.y + cSize.h );
        m_vertices[3].texCoord = Vec2f( cPos.x, cPos.y + cSize.h );
    }
}

void Sprite::onSizeChange(const Vec2f& prevSize) {
    m_vertices[1].pos.x = m_size.x;
    m_vertices[2].pos   = m_size;
    m_vertices[3].pos.y = m_size.y;
}

} // namespace mg
