#pragma once

#include "..\graphics\RectShape.h"

namespace mg {

class Sprite : public RectShape {
public:
    Sprite();

    void draw(Renderer& renderer, RenderStates states) const override;

    void setTexture(const Texture* texture);
    const Texture* getTexture() const;

    void setClip(const iRect& clip);
    void setClip(int x, int y, int w, int h);
    iRect getClip() const;

private:
    void updateClipVertices();

private:
//    VertexArray m_vertices;
    const Texture* m_texture;

    iRect m_clip;
    bool m_isClipSet;   // If clip was set manually
};

} // namespace mg
