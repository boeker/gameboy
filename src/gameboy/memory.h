#ifndef GAMEBOY_MEMORY_H
#define GAMEBOY_MEMORY_H

#include <cinttypes>
#include <string>
#include <fstream>

/* General memory map:
Interrupt Enable Register
--------------------------- FFFF
Internal RAM
--------------------------- FF80
Empty but unusable for I/O
--------------------------- FF4C
I/O ports
--------------------------- FF00
Empty but unusable for I/O
--------------------------- FEA0
Sprite Attrib Memory (OAM)
--------------------------- FE00
Echo of 8kB Internal RAM
--------------------------- E000
8kB Internal RAM
--------------------------- C000
8kB switchable RAM bank
--------------------------- A000
8kB Video RAM
--------------------------- 8000 --
16kB switchable ROM bank |
--------------------------- 4000 |= 32kB Cartridge
16kB ROM bank #0 |
--------------------------- 0000 --
*/

namespace gameboy {
namespace mbc {
class MemoryBankController;
}
}

namespace gameboy {
class Memory {
 public:
    explicit Memory();
    virtual ~Memory();
    void reset();
    void loadROM(const std::string &file);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    void writeRaw(uint16_t address, uint8_t value);
    uint16_t readW(uint16_t address);
    void writeW(uint16_t address, uint16_t value);

 private:
    uint8_t* resolveAddress(uint16_t address);

    uint8_t *ieReg;         // FFFF, 1 byte
    uint8_t *highRam;       // FF80-FFFE, 127 bytes
    uint8_t *ioPorts;       // FEA0-FF7F, 224 bytes
                            // FEA0-FEFF, FF4C-FF7F unusable?
    uint8_t *spriteAttTab;  // FE00-FE9F, 160 bytes
    uint8_t *internalRam;   // C000-DFFF, 8192 bytes
                            // E000-FDFF (7680 bytes) are echoed to this
    uint8_t *externalRam;   // A000-BFFF, 8192 bytes
    uint8_t *videoRam;      // 8000-9FFF, 8192 bytes
    uint8_t *romBank;       // 4000-7FFF, switchable
                            // at least 1x16384 bytes
    uint8_t *rom;           // 0000-3FFF, 16384 bytes

    mbc::MemoryBankController *mbc;
};
}

#endif
