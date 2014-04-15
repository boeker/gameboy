// Copyright (c) 2014 Jan Böker
// MIT License

#include "keyboard.h"

namespace gameboy {
Keyboard::Keyboard() :
    up(false),
    down(false),
    left(false),
    right(false),
    select(false),
    start(false),
    a(false),
    b(false) {
}

Keyboard::~Keyboard() {
}
}
