// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_MBC_MBC1_H
#define GAMEBOY_MBC_MBC1_H

#include <cinttypes>

#include "memorybankcontroller.h"

namespace gameboy {
namespace mbc {
class MBC1 : public MemoryBankController {
 public:
    MBC1(uint8_t **romBanks, uint8_t numBanks);
    virtual uint8_t* getCurrentROMBank();
    virtual void write(uint16_t address, uint8_t value);

 private:
    uint16_t currentROMBank;
};
}
}

#endif