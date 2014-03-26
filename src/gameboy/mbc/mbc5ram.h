/*#ifndef GAMEBOY_MBC_MBC5RAM_H
#define GAMEBOY_MBC_MBC5RAM_H

#include <cinttypes>

#include "memorybankcontroller.h"

namespace gameboy {
namespace mbc {
class MBC5RAM : public MemoryBankController {
 public:
    MBC5RAM(uint8_t **romBanks, uint8_t num, uint8_t **ramBanks, uint8_t numRam);
    virtual ~MBC5RAM();
    virtual uint8_t* getExternalRAM();
    virtual uint8_t* getROMBank();
    virtual void write(uint16_t address, uint8_t value);

 private:
    uint8_t **romBanks;
    uint8_t numOfROMBanks;
    uint16_t currentROMBank;

    uint8_t **ramBanks;
    uint8_t numOfRAMBanks;
    uint16_t currentRAMBank;

    bool ramBanking;
};
}
}

#endif*/