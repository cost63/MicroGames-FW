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

    void setClip(const iRect& clip);
    void setClip(int x, int y, int w, int h);
    iRect getClip() const;

private:
    void updateClipVertices();
    void onSizeChange(const Vec2f& prevSize);

private:
    VertexArray m_vertices;
    const Texture* m_texture;

    iRect m_clip;
    bool m_isClipSet;   // If clip was set manually
};

} // namespace mg
