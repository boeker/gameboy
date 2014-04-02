#include "screen.h"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <QDebug>
#include "memory.h"

namespace gameboy {
Screen::Screen(Memory *memory) :
    memory(memory) {
    framebuffer = new util::Color[160 * 144];

    reset();
    clearFramebuffer();
}

Screen::~Screen() {
    delete[] framebuffer;
}

void Screen::reset() {
    enabled = true;
    drawFlag = false;
    lineRendered = false;
    setLine(144);
    clocks = 0;
    changeMode(VBLANK);
    delay = 0;
}

void Screen::clearFramebuffer() {
    for (int i = 0; i < 160*144; ++i) {
        framebuffer[i] = util::Color::CUR_WHITE;
    }
}

util::Color* Screen::getFramebuffer() {
    return framebuffer;
}

bool Screen::drawFlagSet() {
    return drawFlag;
}

void Screen::enable() {
    delay = 61;
}

void Screen::disable() {
    reset();
    setLine(0);
    changeMode(HBLANK);
    enabled = false;

    clearFramebuffer();
}

void Screen::step(unsigned int lastClocks) {
    drawFlag = false;
    if (memory->read(0xFF40) & 0x80) { // LCD enabled
        if (!enabled && delay == 0) {
            enable();
        }
    } else {
        if (enabled) {
            disable();
        }
    }

    if (enabled) {
        clocks += lastClocks;
        switch (mode) {
            case HBLANK: // Mode 00
                if (clocks >= 51) {
                    clocks -= 51;
                    setLine(line+1);

                    if (line == 144) {
                        changeMode(VBLANK);
                        drawFlag = true;

                        if (memory->read(0xFF41) & 0x10) { // Mode 01 Interrupt
                            memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
                        }

                        memory->write(0xFF0F, memory->read(0xFF0F) | 0x01); //Set V-Blank Interrupt Flag
                    } else {
                        changeMode(OAM);

                        if (memory->read(0xFF41) & 0x20) { // Mode 10 Interrupt
                            memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
                        }
                    }
                }
            break;
            case VBLANK: // Mode 01
                if (clocks >= 114) {
                    clocks -= 114;
                    setLine(line+1);
                    if (line > 153) {
                        changeMode(OAM);
                        setLine(0);

                        if (memory->read(0xFF41) & 0x20) { // Mode 10 Interrupt
                            memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
                        }
                    }
                }
            break;
            case OAM: // Mode 10
                if (clocks >= 20) {
                    clocks -= 20;
                    changeMode(VRAM);
                    lineRendered = false;
                }
            break;
            case VRAM: // Mode 11
                if (!lineRendered && (clocks >= (line ? 12 : 40))) {
                    lineRendered = true;
                    renderScanLine();
                }
                if (clocks >= 43) {
                    clocks -= 43;
                    changeMode(HBLANK);
                    
                    if (memory->read(0xFF41) & 0x08) { // Mode 00 Interrupt
                        memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
                    }
                }
            break;
        }
        compareLYLYC();
    } else {
        if (delay > 0) { // LCD is about to be enabled
            delay -= lastClocks;
            if (delay <= 0) {
                reset();
                enabled = true;
                clocks = -delay;
                delay = 0;
                setLine(0);
                changeMode(HBLANK);
                compareLYLYC();
            }
        } else {
            clocks += lastClocks;
            if (clocks >= 70224) {
                clocks -= 70224;
                drawFlag = true;
            }
        }
    }
}

void Screen::compareLYLYC() {
    // FF41 (STAT)
    uint8_t stat = memory->read(0xFF41);

    uint8_t ly = memory->read(0xFF44);
    uint8_t lyc = memory->read(0xFF45);
    if (lyc == ly) {
        memory->write(0xFF41, stat | 0x04); // Set Coincidence Flag

        if (stat & 0x40) { // LYC=LY Coincidence Interrupt enabled
            memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
        }
    } else {
        memory->write(0xFF41, stat & 0xFB); // Clear Coincidence Flag
    }
}

void Screen::setLine(unsigned int l) {
    line = l;
    memory->write(0xFF44, static_cast<uint8_t>(line));
}

void Screen::changeMode(Mode m) {
    mode = m;

    uint8_t stat = memory->read(0xFF41) & 0xFC;
    stat |= static_cast<uint8_t>(m);
    memory->write(0xFF41, stat);
}

void Screen::renderScanLine() {
    // FF40 - LCDC - LCD Control
    uint8_t lcdc = memory->read(0xFF40);

    // Bit 7 - LCD Display Enable (0=Off, 1=On)
    if (lcdc & 0x80) {
        // Bit 0 - BG Display (0=Off, 1=On)
        if (lcdc & 0x01) {
            renderBackground();
        }

        // Bit 5 - Window Display Enable (0=Off, 1=On)
        if (lcdc & 0x20) {
            renderWindow();
        }

        // Bit 1 - OBJ (Sprite) Display Enable (0=Off, 1=On)
        if (lcdc & 0x02) {
            renderSprites();
        }
    }
}

void Screen::renderBackground() {
    uint8_t palette = memory->read(0xFF47);

    for (int i = 0; i < 4; ++i) {
        bgPalette[i] = util::Color::PALETTE[(palette >> (i*2)) & 0x3];
    }

    // FF40 - LCDC - LCD Control
    uint8_t lcdc = memory->read(0xFF40);
    // Bit 4 - BG & Window Tile Data Select
    uint16_t tileSet = (lcdc & 0x10) ? 0x8000 : 0x9000;
    // Bit 3 - BG Tile Map Display Select
    uint16_t tileMap = (lcdc & 0x08) ? 0x9C00 : 0x9800;

    // Coordinates of background to be displayed in the left upper corner
    uint8_t scrollX = memory->read(0xFF43);
    uint8_t scrollY = memory->read(0xFF42);

    int num;
    uint16_t tileRow = ((scrollY + line) % 256) / 8;
    uint16_t inTileY = ((scrollY + line) % 256) % 8;
    for (int x = 0; x < 160; ++x) {
        uint16_t tileColumn = ((scrollX + x) % 256) / 8;
        uint16_t inTileX = ((scrollX + x) % 256) % 8;

        uint16_t tileNumLocation = tileMap + tileRow * 32 + tileColumn;

        if (tileSet == 0x8000) {
             num = static_cast<uint8_t>(memory->read(tileNumLocation));
        } else {
            num = static_cast<int8_t>(memory->read(tileNumLocation));
        }

        framebuffer[line*160+x] = bgPalette[readTile(tileSet+num*16, inTileX, inTileY)];
    }
}

void Screen::renderWindow() {
    int16_t wndY = memory->read(0xFF4A);
    int16_t wndX = memory->read(0xFF4B) - 0x7;

    // Check if the window is displayed
    if (wndY < 0
        || wndY >= 144
        || wndX < -7
        || wndX >= 160) {
        return;
    }

    // Check if the window is on the current line
    if (wndY > static_cast<int16_t>(line)) {
        return;
    }

    uint8_t palette = memory->read(0xFF47);

    for (int i = 0; i < 4; ++i) {
        bgPalette[i] = util::Color::PALETTE[(palette >> (i*2)) & 0x3];
    }

    // FF40 - LCDC - LCD Control
    uint8_t lcdc = memory->read(0xFF40);
    // Bit 4 - BG & Window Tile Data Select
    uint16_t tileSet = (lcdc & 0x10) ? 0x8000 : 0x9000;
    // Bit 6 - Window Tile Map Display Select
    uint16_t tileMap = (lcdc & 0x40) ? 0x9C00 : 0x9800;

    int num;
    uint16_t tileRow = (line - wndY) / 8;
    uint16_t inTileY = (line - wndY) % 8;

    for (int x = (wndX < 0) ? 0 : wndX; x < 160; ++x) {
        uint16_t tileColumn = (x - wndX) / 8;
        uint16_t inTileX = (x - wndX) % 8;

        uint16_t tileNumLocation = tileMap + tileRow * 32 + tileColumn;

        if (tileSet == 0x8000) {
             num = static_cast<uint8_t>(memory->read(tileNumLocation));
        } else {
            num = static_cast<int8_t>(memory->read(tileNumLocation));
        }

        framebuffer[line*160+x] = bgPalette[readTile(tileSet+num*16, inTileX, inTileY)];
    }
}

void Screen::renderSprites() {
    // Bit 2 - OBJ (Sprite) Size (0=8x8, 1=8x16)
    bool largeSprites = memory->read(0xFF40) & 0x4;

    for (int h = 39; h >= 0; --h) { // Respect sprite priority
        uint16_t currentOAMAddr = 0xFE00 + 0x4 * h;

        // Top left Corner
        // Byte 0 - Y Position - Vertical position on the screen (minus 16).
        int16_t yCoord = memory->read(currentOAMAddr) - 0x10;
        // Byte 1 - X Position - Horizontal position on the screen (minus 8)
        int16_t xCoord = memory->read(currentOAMAddr+1) - 0x8;

        // Check if the sprite is not on the screen
        if (xCoord >= 160
            || xCoord <= -8
            || yCoord >= 144
            || yCoord <= -(largeSprites ? 16 : 8)) {
            continue;
        }

        uint8_t inTileY = line - yCoord;

        // Check if it is not on the current line
        if (yCoord > static_cast<int16_t>(line) || inTileY >= (largeSprites ? 16 : 8)) {
            continue;
        }

        uint8_t optionsByte = memory->read(currentOAMAddr+3);
        bool priority = !(optionsByte & 0x80);
        bool yFlip = optionsByte & 0x40;
        bool xFlip = optionsByte & 0x20;
        uint8_t palette = memory->read((optionsByte & 0x10) ? 0xFF49 : 0xFF48);

        for (int i = 0; i < 4; ++i) {
            spritePalette[i] = util::Color::PALETTE[(palette >> (i*2)) & 0x3];
        }

        // Byte 2 - Pattern number
        uint8_t spriteNum = memory->read(currentOAMAddr+2);

        // Find tile address
        uint16_t tileAddr;

        if (largeSprites) {
            if (yFlip) {
                inTileY = 15 - inTileY;
            }

            // Check which 8x8 tile has to be used
            if (inTileY < 8) {
                tileAddr = 0x8000 + 0x10 * (spriteNum & 0xFE); // Upper tile, ignore LSB
            } else {
                tileAddr = 0x8000 + 0x10 * (spriteNum | 0x01); // Lower tile, set LSB
                inTileY -= 8;
            }
        } else {
            if (yFlip) {
                inTileY = 7 - inTileY;
            }

            tileAddr = 0x8000 + 0x10 * spriteNum;
        }

        for (int x = 0; x < 8; ++x) {
            if (xCoord + x < 0 || xCoord + x >= 160) {
                continue;
            }

            uint8_t pixel = readTile(tileAddr, xFlip ? (7-x) : x, inTileY); // 0 = transparency

            if (pixel && (priority || (framebuffer[line*160+xCoord+x] == bgPalette[0]))) {
                framebuffer[line*160+xCoord+x] = spritePalette[pixel];
            }
        }
    }
}

uint8_t Screen::readTile(uint16_t address, uint8_t x, uint8_t y) {
    uint8_t lsBits = memory->read(address+(y*2));
    uint8_t msBits = memory->read(address+(y*2)+1);

    uint8_t lsb = (lsBits >> (7-x)) & 0x1;
    uint8_t msb = (msBits >> (7-x)) & 0x1;
    uint8_t col = (msb << 1) | lsb;

    return col;
}
}
