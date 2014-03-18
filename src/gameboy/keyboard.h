#ifndef GAMEBOY_KEYBOARD_H
#define GAMEBOY_KEYBOARD_H

#include <atomic>

namespace gameboy {
class Keyboard {
 public:
    Keyboard();
    virtual ~Keyboard();

    std::atomic<bool> up;
    std::atomic<bool> down;
    std::atomic<bool> left;
    std::atomic<bool> right;

    std::atomic<bool> select;
    std::atomic<bool> start;

    std::atomic<bool> a;
    std::atomic<bool> b;
};
}

#endif
