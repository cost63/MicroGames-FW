#include "Init.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../system/ErrorLog.h"
#include "../system/Window.h"
#include "../graphics/OpenGL.h"
#include "../graphics/Renderer.h"

namespace mg {

bool g_isGlewInit = false;

bool init() {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        priv::logError("SDL initialization failed with following errors:\n" +
                       std::string(SDL_GetError()));

        return false;
    }

    // Initialize TTF
    if(TTF_Init() < 0) {
        priv::logError("SDL_ttf initialization failed with following errors:\n" +
                       std::string(TTF_GetError()));

        // Cleanup
        SDL_Quit();

        return false;
    }

    // Set GL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    return true;
}

void close() {
    SDL_Quit();
}

bool initGlew() {
    // If Glew was already initialized
    if(g_isGlewInit) {
        return true;
    }

    // Initialize Glew
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    // Check for Glew init errors
    if( glewError != GL_NO_ERROR ) {
        const char* errMsg = reinterpret_cast<const char*>(glewGetErrorString(glewError));

        priv::logError("Glew initialization failed with following errors:\n" +
                       std::string(errMsg));

        return false;
    }

    g_isGlewInit = true;
    return true;
}

} // namespace mg
