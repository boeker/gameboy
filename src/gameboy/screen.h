#ifndef GAMEBOY_SCREEN_H
#define GAMEBOY_SCREEN_H

#include <cinttypes>
#include "util/color.h"
#include "memory.h"

namespace gameboy {
class Screen {
 public:
    explicit Screen(Memory *memory);
    virtual ~Screen();

    util::Color* getFramebuffer();
    bool drawFlagSet();

    void step(unsigned int lastClocks);

 private:
    void renderScanLine();

    void renderBackground();
    void renderSprites();

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
    util::Color bgColorNull;
    util::Color spColorNull;
    Memory *memory;
};
}

#endif
