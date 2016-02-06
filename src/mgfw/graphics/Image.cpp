#include "image.h"

#include <cstring>
#include <SDL2/SDL_image.h>

#include "../system/ErrorLog.h"

namespace mg {

Image::Image()
{}

Image::~Image() {}

void Image::create(const Vec2u& size, const Color& color /* = Color::Black */) {
    m_size = size;

    if(size.w != 0 && size.h != 0) {
        uint32_t sizeInBytes = size.w * size.h * 4;

        m_pixels.resize(sizeInBytes);

        for(uint32_t i = 0; i < sizeInBytes; i += 4 ) {
            m_pixels[i + 0] = color.r;
            m_pixels[i + 1] = color.g;
            m_pixels[i + 2] = color.b;
            m_pixels[i + 3] = color.a;
        }
    }
    else {
        m_pixels.clear();
    }
}

void Image::create(const Vec2u& size, const uint8_t* pixels) {
    uint32_t sizeInBytes = size.w * size.h * 4;

    m_pixels.resize(sizeInBytes);

    memcpy(&m_pixels[0], pixels, sizeInBytes);
}

bool Image::loadFromFile(const std::string& filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());

    // Check if surface was created
    if(!surface) {
        priv::logError("Failed to load image at: " + filename + "\n" +
                       SDL_GetError());
        return false;
    }

    // Store texture size
    m_size.w = surface->w;
    m_size.h = surface->h;

    m_pixels.resize(m_size.w * m_size.h * 4);

    // If pixel format of the loaded image is not RGBA, change it
    if(surface->format->format != SDL_PIXELFORMAT_RGBA8888) {
        SDL_Surface* formatted = SDL_ConvertSurfaceFormat(surface,
                                                          SDL_PIXELFORMAT_RGBA8888,
                                                          surface->flags);

        // Make sure format conversion went alright
        if(!formatted) {
            priv::logError("Failed to change image format to RGBA from file: " + filename);

            return false;
        }

        // Copy pixels from the formatted surface
        memcpy(&m_pixels[0], formatted->pixels, m_size.w * m_size.h * 4);

        SDL_FreeSurface(formatted);
    }
    else {
        // Copy pixels from the surface
        memcpy(&m_pixels[0], surface->pixels, m_size.w * m_size.h * 4);
    }

    SDL_FreeSurface(surface);

    return true;
}

void Image::setPixel(const Vec2u& pos, const Color& color) {
    uint32_t index = pos.y * m_size.w + pos.x;

    m_pixels[index + 0] = color.r;
    m_pixels[index + 1] = color.g;
    m_pixels[index + 2] = color.b;
    m_pixels[index + 3] = color.a;
}

Color Image::getPixel(const Vec2u& pos) const {
    uint32_t index = pos.y * m_size.w + pos.x;

    Color color;
    color.r = m_pixels[index + 0];
    color.g = m_pixels[index + 1];
    color.b = m_pixels[index + 2];
    color.a = m_pixels[index + 3];

    return color;
}

const uint8_t* Image::getPixels() const {
    return &m_pixels[0];
}

Vec2u Image::getSize() const {
    return m_size;
}

} // namespace mg
