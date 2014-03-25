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
}

Screen::~Screen() {
    delete[] framebuffer;
}

void Screen::reset() {
    drawFlag = false;
    line = 0;
    mode = OAM;

    for (int i = 0; i < 160*144; ++i) {
        framebuffer[i].set(0xFF, 0xFF, 0xFF);
    }
}

util::Color* Screen::getFramebuffer() {
    return framebuffer;
}

bool Screen::drawFlagSet() {
    return drawFlag;
}

void Screen::step(unsigned int lastClocks) {
    clocks += lastClocks;
    drawFlag = false;

    switch (mode) {
        case OAM:
            if (clocks >= 20) {
                clocks = 0;
                mode = VRAM;
                memory->write(0xFF41, memory->read(0xFF41) | 0x03); // Indicate VRAM Mode 11
            }
        break;
        case VRAM:
            if (clocks >= 43) {
                clocks = 0;
                mode = HBLANK;
                renderScanLine();
                memory->write(0xFF41, memory->read(0xFF41) & 0xFC); // Indicate H-Blank Mode 00
                
                if (memory->read(0xFF41) & 0x08) { // Mode 00 Interrupt
                    memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
                }
            }
        break;
        case HBLANK:
            if (clocks >= 51) {
                clocks = 0;
                ++line;
                if (line == 144) {
                    mode = VBLANK;
                    drawFlag = true;
                    memory->write(0xFF41, memory->read(0xFF41) & 0xFD); // Indicate V-Blank Mode 01
                    memory->write(0xFF41, memory->read(0xFF41) | 0x01);

                    if (memory->read(0xFF41) & 0x10) { // Mode 01 Interrupt
                        memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
                    }

                    memory->write(0xFF0F, memory->read(0xFF0F) | 0x01); //Set V-Blank Interrupt Flag
                } else {
                    mode = OAM;
                    memory->write(0xFF41, memory->read(0xFF41) & 0xFE); // Indicate OAM Mode 10
                    memory->write(0xFF41, memory->read(0xFF41) | 0x02);

                    if (memory->read(0xFF41) & 0x20) { // Mode 10 Interrupt
                        memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
                    }
                }
            }
        break;
        case VBLANK:
            if (clocks >= 114) {
                clocks = 0;
                ++line;
                if (line >= 153) {
                    mode = OAM;
                    line = 0;
                    memory->write(0xFF41, memory->read(0xFF41) & 0xFE); // Indicate OAM Mode 10
                    memory->write(0xFF41, memory->read(0xFF41) | 0x02);

                    if (memory->read(0xFF41) & 0x20) { // Mode 10 Interrupt
                        memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); // Set LCD-STAT Interrupt Flag
                    }
                }
            }
        break;
    }
    //FF44 - LY - LCDC Y-Coordinate (R)
    memory->write(0xFF44, static_cast<uint8_t>(line));

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
