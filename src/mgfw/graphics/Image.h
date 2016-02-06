#pragma once

#include <vector>

#include "../math/Vector2.h"
#include "../graphics/Color.h"

namespace mg {

class Image {
public:
    Image();
    ~Image();

    void create(const Vec2u& size, const Color& color = Color::Black);
    void create(const Vec2u& size, const uint8_t* pixels);

    bool loadFromFile(const std::string& filename);

    void setPixel(const Vec2u& pos, const Color& color);
    Color getPixel(const Vec2u& pos) const;

    const uint8_t* getPixels() const;

    Vec2u getSize() const;

private:
    Vec2u m_size;
    std::vector<uint8_t> m_pixels;

};

} // namespace mg
