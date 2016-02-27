#pragma once

#include <vector>

#include "../graphics/Vertex.h"
#include "../graphics/Drawable.h"
#include "../graphics/PrimitiveType.h"

namespace mg {

struct VertexArray : public Drawable {
    /* Iterator */
    class Iterator {
    public:
        Iterator(VertexArray& va, uint32_t index = 0)
        : m_va(va)
        , m_index(index)
        {}

        bool operator!=(const Iterator& other) const {
            return (m_index != other.m_index);
        }

        Iterator& operator++() {
            m_index++;
            return *this;
        }

        Vertex& operator*() {
            return m_va.vertices[m_index];
        }

    private:
        VertexArray&    m_va;
        uint32_t        m_index;
    };

    /* Constant Iterator */
    class ConstIterator {
    public:
        ConstIterator(const VertexArray& va, uint32_t index = 0)
        : m_va(va)
        , m_index(index)
        {}

        bool operator!=(const ConstIterator& other) const {
            return (m_index != other.m_index);
        }

        ConstIterator& operator++() {
            m_index++;
            return *this;
        }

        const Vertex& operator*() const {
            return m_va.vertices[m_index];
        }

    private:
        const VertexArray&  m_va;
        uint32_t            m_index;
    };


    /* Variables */
    std::vector<Vertex> vertices;
    PrimitiveType type;

    bool normalized;
    bool inPixels;

    /* Methods */
    VertexArray();
    VertexArray(PrimitiveType type, uint32_t size = 0);

    Vertex& operator[](uint32_t index);
    const Vertex& operator[](uint32_t index) const;

    void draw(Renderer& renderer, RenderStates states) const override;

    void resize(uint32_t size);
    size_t size() const;
    void clear();
    const Vertex* data() const;

    void push_back(const Vertex& vertex);

    /* Range based iteration methods */
    Iterator begin() {
        return Iterator(*this, 0);
    }

    Iterator end() {
        return Iterator(*this, vertices.size());
    }

    ConstIterator begin() const {
        return ConstIterator(*this, 0);
    }

    ConstIterator end() const {
        return ConstIterator(*this, vertices.size());
    }
};

} // namespace mg
