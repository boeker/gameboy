#ifndef GAMEBOY_MBC_MBC1_H
#define GAMEBOY_MBC_MBC1_H

#include <cinttypes>

#include "memorybankcontroller.h"

namespace gameboy {
namespace mbc {
class MBC1 : public MemoryBankController {
 public:
    MBC1(uint8_t **romBanks, uint8_t num);
    virtual ~MBC1();
    virtual uint8_t* getExternalRAM();
    virtual uint8_t* getROMBank();
    virtual void write(uint16_t address, uint8_t value);

 private:
    uint8_t **romBanks;
    uint8_t numOfROMBanks;
    uint16_t currentROMBank;

    uint8_t *ram;
};
}
}

#endif