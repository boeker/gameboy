// Copyright (c) 2014 Jan Böker
// MIT License

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

    const static Color WHITE;
    const static Color LIGHTGRAY;
    const static Color DARKGRAY;
    const static Color BLACK;

    const static Color DMG_WHITE;
    const static Color DMG_LIGHTGRAY;
    const static Color DMG_DARKGRAY;
    const static Color DMG_BLACK;

    static Color CUR_WHITE;
    static Color CUR_LIGHTGRAY;
    static Color CUR_DARKGRAY;
    static Color CUR_BLACK;

    static Color PALETTE[];
};
}

#endif
