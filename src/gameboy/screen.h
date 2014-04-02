#ifndef GAMEBOY_SCREEN_H
#define GAMEBOY_SCREEN_H

#include <cinttypes>

#include "util/color.h"

namespace gameboy {
class Memory;
}

namespace gameboy {
class Screen {
    enum Mode {
        HBLANK,
        VBLANK,
        OAM,
        VRAM
    };

 public:
    explicit Screen(Memory *memory);
    virtual ~Screen();
    void reset();
    void clearFramebuffer();

    util::Color* getFramebuffer();
    bool drawFlagSet();

    void enable();
    void disable();

    void step(unsigned int lastClocks);

 private:
    void compareLYLYC();
    void setLine(unsigned int l);
    void changeMode(Mode m);

    void renderScanLine();
    void renderBackground();
    void renderWindow();
    void renderSprites();

    uint8_t readTile(uint16_t address, uint8_t x, uint8_t y);

    bool enabled;
    bool drawFlag;
    bool lineRendered;
    unsigned int line;
    unsigned int clocks;
    Mode mode;
    util::Color *framebuffer;
    util::Color bgPalette[4];
    util::Color spritePalette[4];
    Memory *memory;
    int delay;
};
}

#endif
