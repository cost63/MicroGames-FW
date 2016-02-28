#pragma once

#include <vector>
#include <functional>

#include "../system/Keyboard.h"
#include "../math/Vector2.h"

namespace mg {

struct InputEvent {
    struct WindowEvent {
        union {
            struct { int w, h; };
            struct { int x, y; };
        };
    };

    struct KeyEvent {
        Keyboard::Key code;
    };

//    struct UnknownEvent {};

    enum InputEventType {
        /* Window events */
        WindowClosed = 0,
        WindowResized,
        WindowMoved,
        WindowMinimized,
        WindowMaximized,
        WindowMouseEnter,
        WindowMouseLeave,
        WindowFocusGained,
        WindowFocusLost,

        KeyDown,
        KeyUp,

        Unknown
    };

    // This is required as union has to be initialized
//    InputEvent()
//    : key(KeyEvent())
//    {}

    InputEvent::InputEventType type;

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
    using WindowCallback    = std::function<void(const Vec2i&)>;
    using KeyDownCallback   = std::function<void(Keyboard::Key)>;
    using KeyUpCallback     = std::function<void(Keyboard::Key)>;

    struct WindowCBPair {
        WindowCBPair(WindowCallback _callback, uint32_t _ID)
        : callback(_callback)
        , ID(_ID)
        {}

        WindowCallback callback;
        uint32_t ID;
    };
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

    uint32_t addWindowCallback(WindowCallback callback);
    uint32_t addKeyDownCallback(KeyDownCallback callback);
    uint32_t addKeyUpCallback(KeyUpCallback callback);

    void removeCallback(uint32_t ID);

private:
    IDPool m_IDPool;

    std::vector<WindowCBPair>   m_cbWindow;
    std::vector<KeyDownCBPair>  m_cbKeyDown;
    std::vector<KeyUpCBPair>    m_cbKeyUp;

};

} // namespace priv
} // namespace mg
