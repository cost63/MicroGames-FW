#include "VertexArray.h"

namespace mg {

VertexArray::VertexArray()
: type(PrimitiveType::Triangles)
, normalized(false)
{}

VertexArray::VertexArray(PrimitiveType _type, uint32_t size /* = */)
: type(_type)
, normalized(false)
{
    if(size != 0) {
        vertices.resize(size);
    }
}

Vertex& VertexArray::operator[](uint32_t index) {
    return vertices[index];
}

const Vertex& VertexArray::operator[](uint32_t index) const {
    return vertices[index];
}

void VertexArray::draw(Renderer& renderer, RenderStates states) const {
    renderer.draw(*this, states);
}

void VertexArray::resize(uint32_t size) {
    vertices.resize(size);
}

size_t VertexArray::size() const {
    return vertices.size();
}

void VertexArray::clear() {
    vertices.clear();
}

const Vertex* VertexArray::data() const {
    return vertices.data();
}

} // namespace mg
