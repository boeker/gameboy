#include "screen.h"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>

namespace gameboy {
Screen::Screen(Memory *memory)
    :drawFlag(false),
    line(0),
    clocks(0),
    mode(OAM),
    memory(memory) {
    framebuffer = new util::Color[160 * 144];
    mapFrameBuffer = new util::Color*[256];
    for (int i = 0; i < 256; ++i) {
        mapFrameBuffer[i] = new util::Color[256];
    }
    decodedTile = new util::Color*[8];
    for (int i = 0; i < 8; ++i) {
        decodedTile[i] = new util::Color[8];
    }
}

Screen::~Screen() {
    delete[] framebuffer;
    for (int i = 0; i < 256; ++i) {
        delete[] mapFrameBuffer[i];
    }
    delete[] mapFrameBuffer;
    for (int i = 0; i < 8; ++i) {
        delete[] decodedTile[i];
    }
    delete[] decodedTile;
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
            }
        break;
        case VRAM:
            if (clocks >= 43) {
                clocks = 0;
                mode = HBLANK;
                renderScanLine();
            }
        break;
        case HBLANK:
            if (clocks >= 51) {
                clocks = 0;
                ++line;
                if (line == 144) {
                    mode = VBLANK;
                    drawFlag = true;
                } else {
                    mode = OAM;
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
                }
            }
        break;
    }
    //FF44 - LY - LCDC Y-Coordinate (R)
    memory->write(0xFF44, (uint8_t)line);
    //FF45 - LYC - LY Compare (R/W)
    //FF41 (STAT) Bit 6 - LYC=LY Coincidence (Selectable)
    //Bit 2 - Coincidence Flag
    //0: LYC not equal to LCDC LY
    //1: LYC = LCDC LY
    /*if (memory->read(0xFF41) & 0x04) {
        uint8_t ly = memory->read(0xFF44);
        uint8_t lyc = memory->read(0xFF45);
        if (ly == lyc) {
            memory->write(0xFF41, memory->read(0xFF41) | 0x40);
        } else {
            memory->write(0xFF41, memory->read(0xFF41) & 0xBF);
        }
    } else {
        uint8_t ly = memory->read(0xFF44);
        uint8_t lyc = memory->read(0xFF45);
        if (ly != lyc) {
            memory->write(0xFF41, memory->read(0xFF41) | 0x40);
        } else {
            memory->write(0xFF41, memory->read(0xFF41) & 0xBF);
        }
    }*/
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
        switch ((palette >> (i*2)) & 0x3) {
            case 0:
                colors[i] = util::Color(255, 255, 255);
            break;
            case 1:
                colors[i] = util::Color(192, 192, 192);
            break;
            case 2:
                colors[i] = util::Color(96, 96, 96);
            break;
            case 3:
                colors[i] = util::Color(0, 0, 0);
            break;
        }
    }
    bgColorNull = colors[0];

    //Bit 4 - BG & Window Tile Data Select
    uint16_t tileSet = (memory->read(0xFF40) & 0x10) != 0 ? 0x8000 : 0x9000;
    //Bit 3 - BG Tile Map Display Select
    uint16_t tileMap = (memory->read(0xFF40) & 0x8) != 0 ? 0x9C00 : 0x9800;

    //Render the whole map
    if (tileSet == 0x8000) {
        uint8_t num;
        for (int y = 0; y < 32; ++y) {
            for (int x = 0; x < 32; ++x) {
                num = memory->read(tileMap+y*32+x);
                for (int h = 0; h < 8; ++h) {
                    uint8_t lsBits = memory->read(tileSet+num*16+(h*2));
                    uint8_t msBits = memory->read(tileSet+num*16+(h*2)+1);
                    for (int i = 0; i < 8; ++i) {
                        uint8_t lsb = (lsBits >> (7-i)) & 0x1;
                        uint8_t msb = (msBits >> (7-i)) & 0x1;
                        uint8_t col = (msb << 1) | lsb;
                        mapFrameBuffer[y*8+h][x*8+i] = colors[col];
                    }
                }
            }
        }
    } else {
        int8_t num;
        for (int y = 0; y < 32; ++y) {
            for (int x = 0; x < 32; ++x) {
                num = (int8_t)memory->read(tileMap+y*32+x);
                for (int h = 0; h < 8; ++h) {
                    uint8_t lsBits = memory->read(tileSet+num*16+(h*2));
                    uint8_t msBits = memory->read(tileSet+num*16+(h*2)+1);
                    for (int i = 0; i < 8; ++i) {
                        uint8_t lsb = (lsBits >> (7-i)) & 0x1;
                        uint8_t msb = (msBits >> (7-i)) & 0x1;
                        uint8_t col = (msb << 1) | lsb;
                        mapFrameBuffer[y*8+h][x*8+i] = colors[col];
                    }
                }
            }
        }
    }

    //coordinates of background to be displayed in the left upper corner
    uint8_t scrollX = memory->read(0xFF43);
    uint8_t scrollY = memory->read(0xFF42);

    for (int i = 0; i < 160; ++i) {
        framebuffer[line*160+i] = mapFrameBuffer[(scrollY+line) % 0xFF][(scrollX+i) % 0xFF];
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

        decodeTile(tileAddr, palette, yFlip, xFlip);

        for (int i = 0; i < 8; ++i) {
            if ((priority || (framebuffer[line*160+xCoord+i] == util::Color(255, 255, 255))) && !(decodedTile[line-yCoord][i] == util::Color(255, 255, 255))) {
                framebuffer[line*160+xCoord+i] = decodedTile[line-yCoord][i];
            }
        }
    }
}

void Screen::decodeTile(uint16_t tileAddr, uint8_t palette, bool yFlip, bool xFlip) {
    util::Color colors[4];

    for (int i = 0; i < 4; ++i) {
        switch ((palette >> (i*2)) & 0x3) {
            case 0:
                colors[i] = util::Color(255, 255, 255);
            break;
            case 1:
                colors[i] = util::Color(192, 192, 192);
            break;
            case 2:
                colors[i] = util::Color(96, 96, 96);
            break;
            case 3:
                colors[i] = util::Color(0, 0, 0);
            break;
        }
    }
    spColorNull = colors[0];

    for (int h = 0; h < 8; ++h) {
        uint8_t lsBits = memory->read(tileAddr+(h*2));
        uint8_t msBits = memory->read(tileAddr+(h*2)+1);
        for (int i = 0; i < 8; ++i) {
            uint8_t lsb = (lsBits >> (7-i)) & 0x1;
            uint8_t msb = (msBits >> (7-i)) & 0x1;
            uint8_t col = (msb << 1) | lsb;
            decodedTile[yFlip ? 7-h : h][xFlip ? 7-i : i] = colors[col];
        }
    }
}
}
