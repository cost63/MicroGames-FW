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
