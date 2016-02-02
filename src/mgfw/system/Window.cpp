#include "window.h"

#include <SDL2/SDL.h>

#include "..\MGFW.h"
#include "..\graphics\OpenGL.h"
#include "..\system\ErrorLog.h"

namespace mg {

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

bool Window::create(const Vec2i& size, const std::string& title, Flag flags) {
    // Clean up
    close();

    // Make sure SDL video was initialized
    if(!SDL_WasInit(SDL_INIT_VIDEO)) {
        priv::storeError("SDL Video was not initialized yet");

        return false;
    }

    // Create the window
    m_handle = SDL_CreateWindow(title.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                size.w,
                                size.h,
                                flags | SDL_WINDOW_OPENGL);

    m_context = SDL_GL_CreateContext(m_handle);
    // Make sure window context was created, print errors otherwise
    if(!m_context) {
        priv::storeError("Failed to crate window context with following errors:");
        priv::storeError(SDL_GetError());

        // Also make sure to cleanup the window
        SDL_DestroyWindow(m_handle);

        return false;
    }

    // If Glew failed to initialize
    if(!initGlew()) {
        // Clean up
        close();

        return false;
    }

    // Setup renderer buffers
    setupRenderer(size);

    m_isCreated = true;
    return true;
}

void Window::close() {
    if( m_handle ) {
        SDL_DestroyWindow(m_handle);
        SDL_GL_DeleteContext(m_context);
    }

    m_isCreated = false;
}

void Window::clear() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::display() {
    // Render everything inside renderer
    render();

    SDL_GL_SwapWindow(m_handle);
}

void Window::updateView() {
    setViewSize(getSize());
}

void Window::setPos(const Vec2i& pos) {
    SDL_SetWindowPosition(m_handle, pos.x, pos.y);
}

Vec2i Window::getPos() const {
    Vec2i pos;
    SDL_GetWindowPosition(m_handle, &pos.x, &pos.y);

    return pos;
}

void Window::setSize(const Vec2i& size) {
    SDL_SetWindowSize(m_handle, size.w, size.h);
}

Vec2i Window::getSize() const {
    Vec2i size;
    SDL_GetWindowSize(m_handle, &size.w, &size.h);

    return size;
}

bool Window::isCreated() const {
    return m_isCreated;
}

} // namespace mg
