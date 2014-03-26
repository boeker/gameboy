#ifndef GAMEBOY_MBC_MEMORYBANKCONTROLLER_H
#define GAMEBOY_MBC_MEMORYBANKCONTROLLER_H

#include <cinttypes>
#include <string>

namespace gameboy {
namespace mbc {
class MemoryBankController {
 public:
    MemoryBankController(uint8_t **romBanks, uint8_t numBanks);
    virtual ~MemoryBankController();
    virtual uint8_t* getCurrentROMBank() = 0;
    virtual void write(uint16_t address, uint8_t value) = 0;

    virtual void writeRAM(uint16_t address, uint8_t value);
    virtual uint8_t readRAM(uint16_t);
 
 protected:
    uint8_t **romBanks;
    uint8_t numOfROMBanks;

 public:
    static void readSave(uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& saveFile);
    static void writeSave(uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& saveFile);
};
}
}

#endif