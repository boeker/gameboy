#include "color.h"

namespace util {
Color::Color() :
    r(255),
    g(255),
    b(255) {
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    set(r, g, b);
}

void Color::set(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color& Color::operator=(const Color &right) {
    if (this == &right) {
        return *this;
    }

    r = right.r;
    g = right.g;
    b = right.b;

    return *this;
}

bool Color::operator==(const Color &right) const {
    return r == right.r && g == right.g && b == right.b;
}

const Color Color::WHITE = Color(255, 255, 255);
const Color Color::LIGHTGRAY = Color(192, 192, 192);
const Color Color::DARKGRAY = Color(96, 96, 96);
const Color Color::BLACK = Color(0, 0, 0);

const Color Color::DMG_WHITE = Color(0xB8, 0xC2, 0x66);
const Color Color::DMG_LIGHTGRAY = Color(0x7B, 0x8A, 0x32);
const Color Color::DMG_DARKGRAY = Color(0x43, 0x59, 0x1D);
const Color Color::DMG_BLACK = Color(0x13, 0x2C, 0x13);

Color Color::CUR_WHITE = DMG_WHITE;
Color Color::CUR_LIGHTGRAY = DMG_LIGHTGRAY;
Color Color::CUR_DARKGRAY = DMG_DARKGRAY;
Color Color::CUR_BLACK = DMG_BLACK;

Color Color::PALETTE[] = {
    CUR_WHITE, CUR_LIGHTGRAY, CUR_DARKGRAY, CUR_BLACK
};
}
