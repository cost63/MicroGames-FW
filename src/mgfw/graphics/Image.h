#pragma once

#include <vector>

#include "../math/Vector2.h"
#include "../graphics/Color.h"

namespace mg {
namespace priv {

// Returns Image pixel format form SDL pixel format
int getFormatFromSDLFormat(int sdlFormat);

} // namespace priv

class Image {
public:
    enum PixelFormat {
        RGB     = 1,
        RGBA    = 2,
        BGR     = 3,
        BGRA    = 4,
        ARGB    = 5,
        ABGR    = 6,
    };

public:
    Image();
    ~Image();

    void create(const Vec2u& size, const Color& color = Color::Black);
    void create(const Vec2u& size, const uint8_t* pixels);

    bool loadFromFile(const std::string& filename);

    void copyPixels(const uint8_t* pixels, const Vec2u& size, const Vec2u& pos = Vec2u());

    void setPixel(const Vec2u& pos, const Color& color);
    Color getPixel(const Vec2u& pos) const;

    const uint8_t* getPixels() const;

    Vec2u getSize() const;

public:
    static uint8_t* convertPixelFormat(const uint8_t* src, uint32_t pxCount, int from, int to);

private:
    Vec2u m_size;
    std::vector<uint8_t> m_pixels;

};

} // namespace mg
