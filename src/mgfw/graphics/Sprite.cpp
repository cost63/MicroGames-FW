#include "Sprite.h"

#include "../graphics/Texture.h"

namespace mg {

Sprite::Sprite()
: m_texture(nullptr)
, m_isClipSet(false)
{}

void Sprite::draw(Renderer& renderer, RenderStates states) const {
    // Setup/update render states
    states.texture = m_texture;
    states.transform *= getMatrix();

    // Draw sprite
    renderer.draw(m_vertices, states);
}

void Sprite::setTexture(const Texture* texture) {
    m_texture = texture;

    if(texture) {
        const Vec2u tSize = texture->getSize();

        // Set sprite's size to be equal to texture size
        setSize(tSize);

        // If clips were not adjusted yet, set default to whole texture
        if(!m_isClipSet) {
            m_clip.x = 0;
            m_clip.y = 0;
            m_clip.w = tSize.w;
            m_clip.h = tSize.h;
        }

        // Update vertices
        updateClipVertices();
    }
}

const Texture* Sprite::getTexture() const {
    return m_texture;
}

void Sprite::setClip(const iRect& clip) {
    m_clip      = clip;
    m_isClipSet = true;

    updateClipVertices();
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

        // Calculate normalized texture coordinates
        const Vec2f cPos(Vec2f(m_clip.pos()) / tSize);
        const Vec2f cSize(Vec2f(m_clip.size()) / tSize);

        // Set texture clip coordinates
        m_vertices[0].texCoord = cPos;
        m_vertices[1].texCoord = Vec2f(cPos.x + cSize.w, cPos.y);
        m_vertices[2].texCoord = Vec2f(cPos.x + cSize.w, cPos.y + cSize.h);
        m_vertices[3].texCoord = Vec2f(cPos.x, cPos.y + cSize.h);
    }
}

} // namespace mg
