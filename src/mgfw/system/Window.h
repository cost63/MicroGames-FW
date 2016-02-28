#pragma once

#include <string>

//#include "../system/InputManager.h"
#include "../graphics/Renderer.h"
#include "../math/Vector2.h"

/* Forward declarations */
class SDL_Window;

/* Using declarations */
using SDL_GLContext = void*;

namespace mg {

class Window : public Renderer {
public:
    enum Flag {
        Fullscreen  = 0x00000001,
        Shown       = 0x00000004,
        Hidden      = 0x00000008,
        Borderless  = 0x00000010,
        Resizeable  = 0x00000020,
        Minimized   = 0x00000040,
        Maximized   = 0x00000080,
    };

public:
    Window();
    Window(const Vec2i& size, const std::string& title, Flag flags);
    ~Window();

    bool create(const Vec2i& size, const std::string& title, Flag flags);
    void close();

    void clear();
    void display();

    // Update view size to the window size
    void updateView();

    void setPos(const Vec2i& pos);
    Vec2i getPos() const;

    void setSize(const Vec2i& size);
    Vec2i getSize() const;

    bool isCreated() const;

protected:
    SDL_Window* m_handle;
    SDL_GLContext m_context;

    bool m_isCreated;
};

} // namespace mg
