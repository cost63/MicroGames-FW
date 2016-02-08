#pragma once

#include <string>

#include "../graphics/Image.h"

namespace mg {

class Texture {
public:
    Texture();

    bool loadFromFile(const std::string& filename);

    void copyFromImage(const Image& image);

    void setPixels(const uint8_t* pixels, const Vec2u& pos, const Vec2u& size);
    void setPixels(const Image& img, const Vec2u& pos = Vec2u());

    void bind() const;

    uint32_t getHandle() const;
    Vec2u getSize() const;

private:
    void clear();

private:
    uint32_t m_handle;

    Vec2u m_size;
};

} // namespace mg
