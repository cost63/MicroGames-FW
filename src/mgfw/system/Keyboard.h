#pragma once

namespace mg {
namespace Keyboard {

enum Key {
    Unknown = 0,

    A = 4,
    B = 5,
    C = 6,
    D = 7,
    E = 8,
    F = 9,
    G = 10,
    H = 11,
    I = 12,
    J = 13,
    K = 14,
    L = 15,
    M = 16,
    N = 17,
    O = 18,
    P = 19,
    Q = 20,
    R = 21,
    S = 22,
    T = 23,
    U = 24,
    V = 25,
    W = 26,
    X = 27,
    Y = 28,
    Z = 29,

    Key_1 = 30,
    Key_2 = 31,
    Key_3 = 32,
    Key_4 = 33,
    Key_5 = 34,
    Key_6 = 35,
    Key_7 = 36,
    Key_8 = 37,
    Key_9 = 38,
    Key_0 = 39,

    Return = 40,
    Escape = 41,
    Backspace = 42,
    Tab = 43,
    Space = 44,
};

} // namespace Keyboard

bool isKeyPressed(Keyboard::Key key);

} // namespace mg
