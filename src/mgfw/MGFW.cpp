#include "MGFW.h"

#include <SDL2/SDL.h>

#include "system/ErrorLog.h"
#include "system/Window.h"
#include "graphics/OpenGL.h"
#include "graphics/Renderer.h"

namespace mg {

bool g_isGlewInit = false;

bool init() {
    // Make sure SDL video was initialized
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        PRINT_ERROR("SDL initialization failed with following errors:");
        PRINT_ERROR(SDL_GetError());
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
        PRINT_ERROR("Glew initialization failed with following errors:");
        PRINT_ERROR(glewGetErrorString(glewError));

        return false;
    }

    g_isGlewInit = true;
    return true;
}

} // namespace mg
