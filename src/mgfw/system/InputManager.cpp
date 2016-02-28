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
        if(sdlEvent.type == SDL_QUIT) {
            event.type = InputEvent::WindowClose;
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

uint32_t InputManager::addKeyDownCallback(KeyDownCallback callback) {
    m_cbKeyDown.push_back({ callback, m_IDPool.ID++ });

    return m_IDPool.ID - 1;
}

uint32_t InputManager::addKeyUpCallback(KeyUpCallback callback) {
    m_cbKeyUp.push_back({ callback, m_IDPool.ID++ });

    return m_IDPool.ID - 1;
}

void InputManager::removeCallback(uint32_t ID) {
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
