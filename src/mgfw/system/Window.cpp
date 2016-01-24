#include "window.h"

#include <SDL2/SDL.h>

#include "..\graphics\OpenGL.h"
#include "..\system\ErrorLog.h"

namespace mg
{

Window::Window()
: m_handle(nullptr)
, m_context(nullptr)
, m_isCreated(false)
{}


Window::Window(const Vec2i& size, const std::string& title, Flag flags)
: Window()
{
    create(size, title, flags);
}

Window::~Window()
{
    close();
}

void Window::create(const Vec2i& size, const std::string& title, Flag flags)
{
    // Make sure SDL video was initialized
    if(!SDL_WasInit(SDL_INIT_VIDEO))
    {
        PRINT_ERROR("SDL Video was not initialized yet");
        return;
    }

    // Create the window
    m_handle = SDL_CreateWindow(title.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                size.w,
                                size.h,
                                flags | SDL_WINDOW_OPENGL);

    // Make sure window was created, print errors otherwise
    if(!m_handle)
    {
        PRINT_ERROR("Failed to create window handle with following errors:");
        PRINT_ERROR(SDL_GetError());

        return;
    }

    m_context = SDL_GL_CreateContext(m_handle);
    // Make sure window context was created, print errors otherwise
    if(!m_context)
    {
        PRINT_ERROR("Failed to crate window context with following errors:");
        PRINT_ERROR(SDL_GetError());

        // Also make sure to cleanup the window
        SDL_DestroyWindow(m_handle);

        return;
    }

    // Initialize Glew
    // TODO(All) Find a better way to initialize Glew with window
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();

    // Check for Glew init errors
    if( glewError != GL_NO_ERROR ) {
        PRINT_ERROR("Glew initialization failed with following errors:");
        PRINT_ERROR(glewGetErrorString(glewError));

        return;
    }

    m_isCreated = true;
}

void Window::close()
{
    if( m_handle )
    {
        SDL_DestroyWindow(m_handle);
        SDL_GL_DeleteContext(m_context);
    }

    m_isCreated = false;
}

void Window::clear()
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::display()
{
    SDL_GL_SwapWindow(m_handle);
}

bool Window::isCreated() const
{
    return m_isCreated;
}

} // namespace mg
