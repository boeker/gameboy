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
}
