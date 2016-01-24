#include "MGFW.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include "system/ErrorLog.h"

namespace mg
{

bool init()
{
    // Make sure SDL video was initialized
    if(SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        PRINT_ERROR("SDL initialization failed with following errors:");
        PRINT_ERROR(SDL_GetError());
        return false;
    }

    // Set GL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    return true;
}

void close()
{
    SDL_Quit();
}

} // namespace mg
