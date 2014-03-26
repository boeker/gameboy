#ifndef GAMEBOY_MBC_MBC5_H
#define GAMEBOY_MBC_MBC5_H

#include <cinttypes>

#include "memorybankcontroller.h"

namespace gameboy {
namespace mbc {
class MBC5 : public MemoryBankController {
 public:
    MBC5(uint8_t **romBanks, uint8_t numBanks);
    virtual uint8_t* getCurrentROMBank();
    virtual void write(uint16_t address, uint8_t value);

 private:
    uint16_t currentROMBank;
};
}
}

#endif