#ifndef UTIL_COLOR_H
#define UTIL_COLOR_H

#include <cinttypes>

namespace util {
class Color {
 public:
    Color();
    Color(uint8_t, uint8_t, uint8_t);
    void set(uint8_t, uint8_t, uint8_t);

    Color& operator=(const Color &);
    bool operator==(const Color &) const;

    uint8_t r;
    uint8_t g;
    uint8_t b;
};
}

#endif
