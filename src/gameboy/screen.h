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
    void decodeTile(uint16_t tileAddr, uint8_t palette,
                    bool yFlip, bool xFlip);

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
    util::Color **mapFrameBuffer;
    util::Color **decodedTile;
    Memory *memory;
};
}

#endif
