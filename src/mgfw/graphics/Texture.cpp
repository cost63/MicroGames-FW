#include "Texture.h"

#include <SDL2/SDL_image.h>

#include "../system/ErrorLog.h"
#include "../graphics/OpenGL.h"

namespace mg {

Texture::Texture()
: m_handle(0)
{}

bool Texture::loadFromFile(const std::string& filename) {
    clear();

    SDL_Surface* surface = IMG_Load(filename.c_str());

    // Check if surface was created
    if(!surface) {
        PRINT_ERROR("Failed to load image at: " + filename);
        PRINT_ERROR(SDL_GetError());
        return false;
    }

    // Store texture size
    m_size.w = surface->w;
    m_size.h = surface->h;

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
            GL_RGB,             // Format
            GL_UNSIGNED_BYTE,   // Type
            surface->pixels     // Data
    );

    // Set filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_handle);
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
