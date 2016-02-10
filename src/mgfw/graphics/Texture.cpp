#include "Texture.h"

#include <SDL2/SDL_image.h>

#include "../system/ErrorLog.h"
#include "../graphics/OpenGL.h"

namespace mg {

Texture::Texture()
: m_handle(0)
{}

bool Texture::loadFromFile(const std::string& filename) {
    Image image;

    bool result = image.loadFromFile(filename);

    if(result) {
        copyFromImage(image);
    }

    return result;
}

void Texture::copyFromImage(const Image& image) {
    clear();

    // Store texture size
    m_size = image.getSize();

    // Generate new texture in OpenGL
    glGenTextures(1, &m_handle);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, m_handle);

    // Setup texture
    glTexImage2D(
            GL_TEXTURE_2D,      // Target
            0,                  // Level
            GL_RGBA,            // Internal format
            m_size.w,           // Width
            m_size.h,           // Height
            0,                  // Border
            GL_ABGR_EXT,        // Format   - SDL format is reversed => SDL_RGBA == GL_ABGR
            GL_UNSIGNED_BYTE,   // Type
            image.getPixels()   // Data
    );

    // Set filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setPixels(const uint8_t* pixels, const Vec2u& pos, const Vec2u& size) {
    if(size > m_size) {
        priv::logError("Unable to set texture pixels. Given size is too large",
                       "[Warning]");
        return;
    }

    if(m_handle && pixels) {
        // Bind this texture
        glBindTexture(GL_TEXTURE_2D, m_handle);

        // Update textures pixels
        glTexSubImage2D(
                GL_TEXTURE_2D,      // target
                0,                  // level
                pos.x,              // X-position
                pos.y,              // Y-position
                size.w,             // width
                size.h,             // height
                GL_RGBA,            // format
                GL_UNSIGNED_BYTE,   // pixels type
                pixels              // pixel data
        );
    }
}

Image Texture::copyToImage() const {
    Image image;

    // Make sure the texture was created
    if(m_handle) {
        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, m_handle);

        uint8_t* pixels = new uint8_t[m_size.w * m_size.h];

        glGetTexImage(
                GL_TEXTURE_2D,      // target
                0,                  // level
                GL_RGBA,            // format
                GL_UNSIGNED_BYTE,   // pixels type
                pixels              // pixel data
        );

        image.create(m_size, pixels);
    }

    return image;
}

void Texture::setPixels(const Image& img, const Vec2u& pos /*= Vec2u() */) {
    setPixels(img.getPixels(), pos, img.getSize());
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

uint32_t Texture::getHandle() const {
    return m_handle;
}

Vec2u Texture::getSize() const {
    return m_size;
}

/* Private */

void Texture::clear() {
    m_handle = 0;
    m_size = Vec2u();
}

} // namespace mg
