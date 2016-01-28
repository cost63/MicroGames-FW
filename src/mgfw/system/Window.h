#pragma once

#include <string>

#include "../graphics/Renderer.h"
#include "../math/Vector2.h"

/* Forward declarations */
class SDL_Window;

/* Using declarations */
using SDL_GLContext = void*;

namespace mg
{

class Window : public Renderer
{
public:
    enum Flag
    {
        Shown = 0x00000004,
    };

public:
    Window();
    Window(const Vec2i& size, const std::string& title, Flag flags);
    ~Window();

    bool create(const Vec2i& size, const std::string& title, Flag flags);
    void close();

    void clear();
    void display();

    void setSize(const Vec2i& size);
    Vec2i getSize() const;

    bool isCreated() const;

protected:
    SDL_Window* m_handle;
    SDL_GLContext m_context;

    bool m_isCreated;
};

} // namespace mg
