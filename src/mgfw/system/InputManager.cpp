#include "InputManager.h"

#include <SDL2/SDL.h>

namespace mg {
namespace priv {

InputManager::InputManager()
{}

bool InputManager::pollEvent(InputEvent& event) {
    SDL_Event sdlEvent;

    if(!SDL_PollEvent(&sdlEvent)) {
        return false;
    }
    else {
        event.type = InputEvent::Unknown;

        if(sdlEvent.type == SDL_QUIT) {
            event.type = InputEvent::WindowClosed;
        }
        else if(sdlEvent.type == SDL_WINDOWEVENT) {
            if(sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
                event.type      = InputEvent::WindowResized;
                event.window.w  = sdlEvent.window.data1;
                event.window.h  = sdlEvent.window.data2;
            }
            else if(sdlEvent.window.event == SDL_WINDOWEVENT_MOVED) {
                event.type      = InputEvent::WindowMoved;
                event.window.x  = sdlEvent.window.data1;
                event.window.y  = sdlEvent.window.data2;
            }
            else if(sdlEvent.window.event == SDL_WINDOWEVENT_MINIMIZED) {
                event.type = InputEvent::WindowMinimized;
            }
            else if(sdlEvent.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
                event.type = InputEvent::WindowMaximized;
            }
            else if(sdlEvent.window.event == SDL_WINDOWEVENT_ENTER) {
                event.type = InputEvent::WindowMouseEnter;
            }
            else if(sdlEvent.window.event == SDL_WINDOWEVENT_LEAVE) {
                event.type = InputEvent::WindowMouseLeave;
            }
            else if(sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                event.type = InputEvent::WindowFocusGained;
            }
            else if(sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                event.type = InputEvent::WindowFocusLost;
            }
        }
        else if(sdlEvent.type == SDL_KEYDOWN) {
            event.type = InputEvent::KeyDown;
            event.key.code = static_cast<Keyboard::Key>(sdlEvent.key.keysym.scancode);

            for(auto pair : m_cbKeyDown) {
                pair.callback(event.key.code);
            }
        }
        else if(sdlEvent.type == SDL_KEYUP) {
            event.type = InputEvent::KeyUp;
            event.key.code = static_cast<Keyboard::Key>(sdlEvent.key.keysym.scancode);

            for(auto pair : m_cbKeyUp) {
                pair.callback(event.key.code);
            }
        }

        return true;
    }
}

uint32_t InputManager::addWindowCallback(WindowCallback callback) {
    m_cbWindow.push_back({ callback, m_IDPool.ID++ });

    return m_IDPool.ID - 1;
}

uint32_t InputManager::addKeyDownCallback(KeyDownCallback callback) {
    m_cbKeyDown.push_back({ callback, m_IDPool.ID++ });

    return m_IDPool.ID - 1;
}

uint32_t InputManager::addKeyUpCallback(KeyUpCallback callback) {
    m_cbKeyUp.push_back({ callback, m_IDPool.ID++ });

    return m_IDPool.ID - 1;
}

void InputManager::removeCallback(uint32_t ID) {
    for(auto it = m_cbWindow.begin(); it != m_cbWindow.end(); it++) {
        if(it->ID == ID) {
            *it = m_cbWindow.back();
            m_cbWindow.pop_back();

            return;
        }
    }

    for(auto it = m_cbKeyDown.begin(); it != m_cbKeyDown.end(); it++) {
        if(it->ID == ID) {
            *it = m_cbKeyDown.back();
            m_cbKeyDown.pop_back();

            return;
        }
    }

    for(auto it = m_cbKeyUp.begin(); it != m_cbKeyUp.end(); it++) {
        if(it->ID == ID) {
            *it = m_cbKeyUp.back();
            m_cbKeyUp.pop_back();

            return;
        }
    }
}

} // namespace priv
} // namespace mg
