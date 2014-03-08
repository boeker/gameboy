#ifndef GAMEBOY_KEYBOARD_H
#define GAMEBOY_KEYBOARD_H

namespace gameboy {
class Keyboard {
 public:
    Keyboard();
    virtual ~Keyboard();

    bool up;
    bool down;
    bool left;
    bool right;

    bool select;
    bool start;

    bool a;
    bool b;
};
}

#endif
