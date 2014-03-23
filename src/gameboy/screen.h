#ifndef GAMEBOY_SCREEN_H
#define GAMEBOY_SCREEN_H

#include <cinttypes>

#include "util/color.h"

namespace gameboy {
class Memory;
}

namespace gameboy {
class Screen {
 public:
    explicit Screen(Memory *memory);
    virtual ~Screen();
    void reset();

    util::Color* getFramebuffer();
    bool drawFlagSet();

    void step(unsigned int lastClocks);

 private:
    void renderScanLine();

    void renderBackground();
    void renderSprites();

    const util::Color& getColor(int i);
    uint8_t readTile(uint16_t address, uint8_t x, uint8_t y);

    enum Mode {
        OAM,
        VRAM,
        HBLANK,
        VBLANK
    };

    bool drawFlag;
    unsigned int line;
    unsigned int clocks;
    Mode mode;
    util::Color *framebuffer;
    util::Color bgPalette[4];
    util::Color spritePalette[4];
    Memory *memory;
};
}

#endif
