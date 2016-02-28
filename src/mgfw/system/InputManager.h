#pragma once

#include <vector>
#include <functional>

#include "../system/Keyboard.h"

namespace mg {

struct WindowEvent {
    enum WindowEventType {

    };

    WindowEventType type;
};

struct KeyEvent {
    Keyboard::Key code = Keyboard::Unknown;
};

struct InputEvent {
    // This is required as union has to be initialized
    InputEvent()
    : key(KeyEvent())
    {}

    enum InputType {
        WindowClose = 1,
        KeyDown     = 2,
        KeyUp       = 3,
    };

    InputEvent::InputType type;

    union {
        WindowEvent window;
        KeyEvent key;
    };
};

namespace priv {

struct IDPool {
    IDPool(uint32_t base = 1)
    : ID(base)
    {}

    uint32_t ID;
};

class InputManager {
private:
    using KeyDownCallback   = std::function<void(Keyboard::Key)>;
    using KeyUpCallback     = std::function<void(Keyboard::Key)>;

    struct KeyDownCBPair {
        KeyDownCBPair(KeyDownCallback _callback, uint32_t _ID)
        : callback(_callback)
        , ID(_ID)
        {}

        KeyDownCallback callback;
        uint32_t ID;
    };
    struct KeyUpCBPair {
        KeyUpCBPair(KeyUpCallback _callback, uint32_t _ID)
        : callback(_callback)
        , ID(_ID)
        {}

        KeyUpCallback callback;
        uint32_t ID;
    };

public:
    InputManager();

    bool pollEvent(InputEvent& event);

    uint32_t addKeyDownCallback(KeyDownCallback callback);
    uint32_t addKeyUpCallback(KeyUpCallback callback);

    void removeCallback(uint32_t ID);

private:
    IDPool m_IDPool;

    std::vector<KeyDownCBPair> m_cbKeyDown;
    std::vector<KeyUpCBPair> m_cbKeyUp;

};

} // namespace priv
} // namespace mg
