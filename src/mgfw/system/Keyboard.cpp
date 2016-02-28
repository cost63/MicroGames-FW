#include "Keyboard.h"

#include <SDL2/SDL.h>

namespace mg {

bool isKeyPressed(Keyboard::Key key) {
    const uint8_t* keys = SDL_GetKeyboardState(nullptr);

    return keys[key];
}

} // namespace mg
