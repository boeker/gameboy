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
                memory->write(0xFF41, memory->read(0xFF41) | 0x03); // Indicate VRAM Mode 00
            }
        break;
        case VRAM:
            if (clocks >= 43) {
                clocks = 0;
                mode = HBLANK;
                renderScanLine();
                memory->write(0xFF41, memory->read(0xFF41) & 0xFC); // Indicate H-Blank Mode 00
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
                    memory->write(0xFF0F, memory->read(0xFF0F) | 0x01); //Set V-Blank Interrupt Flag
                } else {
                    mode = OAM;
                    memory->write(0xFF41, memory->read(0xFF41) & 0xFE); // Indicate OAM Mode 10
                    memory->write(0xFF41, memory->read(0xFF41) | 0x02);
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
                }
            }
        break;
    }
    //FF44 - LY - LCDC Y-Coordinate (R)
    memory->write(0xFF44, (uint8_t)line);

    // FF41 (STAT)
    uint8_t ff41 = memory->read(0xFF41);
    if (ff41 & 0x40) { // LYC=LY Coincidence Interrupt enabled
        uint8_t ly = memory->read(0xFF44);
        uint8_t lyc = memory->read(0xFF45);

        if (ff41 & 0x04) { // LYC = LY Interrupt
            if (ly == lyc) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); //Set LCD-STAT Interrupt Flag
            }
        } else { // LYC != LY Interrupt
            if (ly != lyc) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); //Set LCD-STAT Interrupt Flag
            } 
        }
    }
    if (ff41 & 0x20) { // Mode 10 = 0x2
        if ((ff41 & 0x3) == 0x2) {
            memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); //Set LCD-STAT Interrupt Flag
        }
    }
    if (ff41 & 0x10) { // Mode 01 = 0x1
        if ((ff41 & 0x3) == 0x1) {
            memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); //Set LCD-STAT Interrupt Flag
        }
    }
    if (ff41 & 0x08) { // Mode 00 = 0x0
        if ((ff41 & 0x3) == 0x0) {
            memory->write(0xFF0F, memory->read(0xFF0F) | 0x02); //Set LCD-STAT Interrupt Flag
        }
    }
}

void Screen::renderScanLine() {
    //Bit 7 - LCD Display Enable (0=Off, 1=On)
    if (memory->read(0xFF40) & 0x80) {
        //Bit 0 - BG Display (0=Off, 1=On)
        if (memory->read(0xFF40) & 0x01) {
            renderBackground();
        }
        //Bit 1 - OBJ (Sprite) Display Enable (0=Off, 1=On)
        if (memory->read(0xFF40) & 0x02) {
            renderSprites();
        }
    }
}

void Screen::renderBackground() {
    uint8_t palette = memory->read(0xFF47);
    util::Color colors[4];

    for (int i = 0; i < 4; ++i) {
        colors[i] = getColor((palette >> (i*2)) & 0x3);
    }

    //Bit 4 - BG & Window Tile Data Select
    uint16_t tileSet = (memory->read(0xFF40) & 0x10) ? 0x8000 : 0x9000;
    //Bit 3 - BG Tile Map Display Select
    uint16_t tileMap = (memory->read(0xFF40) & 0x08) ? 0x9C00 : 0x9800;

    //coordinates of background to be displayed in the left upper corner
    uint8_t scrollX = memory->read(0xFF43);
    uint8_t scrollY = memory->read(0xFF42);

    int num;

    uint16_t tileRow = ((scrollY + line) % 0xFF) / 8;
    uint16_t inTileY = ((scrollY + line) % 0xFF) % 8;
    for (int x = 0; x < 160; ++x) {
        uint16_t tileColumn = ((scrollX + x) % 0xFF) / 8;
        uint16_t inTileX = ((scrollX + x) % 0xFF) % 8;

        uint16_t tileNumLocation = tileMap + tileRow * 32 + tileColumn;

        if (tileSet == 0x8000) {
             num = (uint8_t)memory->read(tileNumLocation);
        } else {
            num = (int8_t)memory->read(tileNumLocation);
        }

        framebuffer[line*160+x] = colors[readTile(tileSet+num*16, inTileX, inTileY)];
    }
}

void Screen::renderSprites() {
    for (int h = 0; h < 40; ++h) {
        uint16_t currentOAMAddr = 0xFE00 + 0x4 * h;

        //Byte0 - Y Position - Vertical position on the screen (minus 16).
        uint8_t yCoord = memory->read(currentOAMAddr) - 0x10;
        //Byte1 - X Position - Horizontal position on the screen (minus 8)
        uint8_t xCoord = memory->read(currentOAMAddr+1) - 0x8;

        //Bit 2 - OBJ (Sprite) Size (0=8x8, 1=8x16)
        bool largeSprites = memory->read(0xFF40) & 0x4;

        //Check if the sprite is not visible
        if (xCoord >= 160 || yCoord >= 144) {
            continue;
        }

        //Check if it is not on the current line
        if (yCoord > line || (line - yCoord) >= (largeSprites ? 16 : 8)) {
            continue;
        }

        uint8_t optionsByte = memory->read(currentOAMAddr+3);
        bool priority = !(optionsByte & 0x80);
        bool yFlip = optionsByte & 0x40;
        bool xFlip = optionsByte & 0x20;
        uint8_t palette = memory->read((optionsByte & 0x10) ? 0xFF49 : 0xFF48);

        util::Color colors[4];

        for (int i = 0; i < 4; ++i) {
            colors[i] = getColor((palette >> (i*2)) & 0x3);
        }

        uint8_t spriteNum = memory->read(currentOAMAddr+2);
        uint16_t tileAddr;

        if (!largeSprites) {
            tileAddr = 0x8000 + 0x10 * spriteNum;
        } else {
            //Check which 8x8 tile has to be used
            if ((line - yCoord) < 8) {
                tileAddr = 0x8000 + 0x10 * (spriteNum & 0xFE); //upper
            } else {
                tileAddr = 0x8000 + 0x10 * (spriteNum | 0x01); //lower
            }
        }

        for (int i = 0; i < 8; ++i) {
            uint8_t y = line - yCoord;
            uint8_t pixel = readTile(tileAddr, xFlip ? (7-i) : i, yFlip ? (7-y) : y);

            if ((priority || (framebuffer[line*160+xCoord+i] == util::Color(255, 255, 255))) && !(colors[pixel] == util::Color(255, 255, 255))) {
                framebuffer[line*160+xCoord+i] = colors[pixel];
            }
        }
    }
}

const util::Color& Screen::getColor(int i) {
    switch (i) {
        case 0:
            return util::Color::GBWHITE;
        break;
        case 1:
            return util::Color::GBLIGHTGRAY;
        break;
        case 2:
            return util::Color::GBDARKGRAY;
        break;
        case 3:
            return util::Color::GBBLACK;
        break;
        default:
            return util::Color::GBWHITE;
        break;
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
