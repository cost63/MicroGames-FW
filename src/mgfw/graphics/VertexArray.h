#pragma once

#include <vector>

#include "../graphics/Vertex.h"
#include "../graphics/PrimitiveType.h"

namespace mg {

struct VertexArray {
    VertexArray();
    VertexArray(PrimitiveType type, uint32_t size = 0);

    Vertex& operator[](uint32_t index);
    const Vertex& operator[](uint32_t index) const;

    void resize(uint32_t size);
    size_t size() const;
    const Vertex* data() const;

    std::vector<Vertex> vertices;
    PrimitiveType type;
};

} // namespace mg
