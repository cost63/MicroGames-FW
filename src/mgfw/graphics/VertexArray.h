#pragma once

#include <vector>

#include "../graphics/Vertex.h"
#include "../graphics/Drawable.h"
#include "../graphics/PrimitiveType.h"

namespace mg {

struct VertexArray : public Drawable {
    VertexArray();
    VertexArray(PrimitiveType type, uint32_t size = 0);

    Vertex& operator[](uint32_t index);
    const Vertex& operator[](uint32_t index) const;

    void draw(Renderer& renderer, RenderStates states) const;

    void resize(uint32_t size);
    size_t size() const;
    const Vertex* data() const;

    std::vector<Vertex> vertices;
    PrimitiveType type;

    bool normalized;
};

} // namespace mg
