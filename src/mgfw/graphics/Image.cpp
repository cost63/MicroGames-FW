#include "image.h"

#include <cstring>
#include <SDL2/SDL_image.h>

#include "../system/ErrorLog.h"

namespace mg {
namespace priv {

int getFormatFromSDLFormat(int sdlFormat) {
    int result = 0;

    switch(sdlFormat) {
    // RGB
    case SDL_PIXELFORMAT_RGB888:
    case SDL_PIXELFORMAT_RGB24:     result = Image::RGB; break;
    // RGBA
    case SDL_PIXELFORMAT_RGBA8888:  result = Image::RGBA; break;
    // BGR
    case SDL_PIXELFORMAT_BGR888:
    case SDL_PIXELFORMAT_BGR24:     result = Image::BGR; break;
    // BGRA
    case SDL_PIXELFORMAT_BGRA8888:  result = Image::BGRA; break;
    // ARGB
    case SDL_PIXELFORMAT_ARGB8888:  result = Image::ARGB; break;
    // ABGR
    case SDL_PIXELFORMAT_ABGR8888:  result = Image::ABGR; break;
    default: break;
    }

    return result;
}

} // namespace priv

Image::Image()
{}

Image::~Image() {}

void Image::create(const Vec2u& size, const Color& color /* = Color::Black */) {
    m_size = size;

    if(size.w != 0 && size.h != 0) {
        uint32_t sizeInBytes = size.w * size.h * 4;

        m_pixels.resize(sizeInBytes);

        for(uint32_t i = 0; i < sizeInBytes; i += 4 ) {
            m_pixels[i + 3] = color.r;
            m_pixels[i + 2] = color.g;
            m_pixels[i + 1] = color.b;
            m_pixels[i + 0] = color.a;
        }
    }
    else {
        m_pixels.clear();
    }
}

void Image::create(const Vec2u& size, const uint8_t* pixels) {
    uint32_t sizeInBytes = size.w * size.h * 4;

    m_pixels.resize(sizeInBytes);

    m_size = size;

    memcpy(&m_pixels[0], pixels, sizeInBytes);
}

bool Image::loadFromFile(const std::string& filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());

    // Check if surface was created
    if(!surface) {
        priv::logError("Failed to load image at: " + filename + "\n\t" +
                       SDL_GetError());
        return false;
    }

    // Store texture size
    m_size.w = surface->w;
    m_size.h = surface->h;

    const uint32_t sizeInBytes = m_size.w * m_size.h * 4;
    const uint32_t format = surface->format->format;

    m_pixels.resize(sizeInBytes);

    // If pixel format of the loaded image is not RGBA, change it
    if(format != SDL_PIXELFORMAT_RGBA8888) {
        SDL_Surface* formatted = SDL_ConvertSurfaceFormat(surface,
                                                          SDL_PIXELFORMAT_RGBA8888,
                                                          surface->flags);

        if(!formatted) {
            priv::addError("Failed to convert image format from ");
            priv::addError(std::string(SDL_GetPixelFormatName(format)));
            priv::addError(" to ");
            priv::addError(std::string(SDL_GetPixelFormatName(SDL_PIXELFORMAT_RGBA8888)));
            priv::addError("\n\tfile: " + filename);
            priv::logError();
        }

        memcpy(&m_pixels[0], formatted->pixels, sizeInBytes);

        SDL_FreeSurface(formatted);
    }
    else {
        // Copy pixels from the surface
        memcpy(&m_pixels[0], surface->pixels, sizeInBytes);
    }

    SDL_FreeSurface(surface);

    return true;
}

void Image::copyPixels(const uint8_t* pixels, const Vec2u& size, const Vec2u& pos /*= Vec2u()*/) {
    // If position exceeds image size, copy nothing
    if(pos > m_size) {
        return;
    }

    // Make sure size of the copy area does not exceed image size
    const Vec2u clampedSize = Vec2u(
            m_size.w - pos.x < size.w ? m_size.w - pos.x : size.w,
            m_size.h - pos.y < size.h ? m_size.h - pos.y : size.h
    );

    // Copy pixels
    for(uint16_t y = 0; y < clampedSize.h; y++) {
        uint32_t toIndex    = ((pos.y + y) * m_size.w + pos.x) * 4;
        uint32_t fromIndex  = (y * clampedSize.w) * 4;

        // Copy the whole row of pixels
        memcpy(m_pixels.data() + toIndex, pixels + fromIndex, clampedSize.w * 4);
    }
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

/* Static */

uint8_t* Image::convertPixelFormat(
                    const uint8_t* src,
                    uint32_t pxCount,
                    int from,
                    int to)
{
    const auto getFormatSize = [=](int format) {
        switch(format) {
        case Image::RGB:  return 3; break;
        case Image::BGR:  return 3; break;
        case Image::RGBA: return 4; break;
        case Image::BGRA: return 4; break;
        case Image::ARGB: return 4; break;
        case Image::ABGR: return 4; break;
        default:          return 0; break;
        }
    };

    const uint32_t toFormatSize   = getFormatSize(to);

    uint32_t size   = pxCount * toFormatSize;
    uint8_t* pixels = new uint8_t[size];

    if(from == Image::ARGB) {
        if(to == Image::RGBA) {
            for(uint32_t i = 0; i < size; i += 4) {
                pixels[i + 2] = src[i + 0];
                pixels[i + 1] = src[i + 1];
                pixels[i + 0] = src[i + 2];
                pixels[i + 3] = src[i + 3];
            }
        }
    }

    return pixels;
}

} // namespace mg
