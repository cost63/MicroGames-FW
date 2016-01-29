#pragma once

#include <string>

#include "../math/Vector2.h"

namespace mg {

class Texture {
public:
    Texture();

    bool loadFromFile(const std::string& filename);

    void bind();

    Vec2u getSize() const;

private:
    void clear();

private:
    uint32_t m_handle;

    Vec2u m_size;
};

} // namespace mg
