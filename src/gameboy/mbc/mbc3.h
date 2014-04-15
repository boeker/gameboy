// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_MBC_MBC3_H
#define GAMEBOY_MBC_MBC3_H

#include <cinttypes>

#include "memorybankcontroller.h"

namespace gameboy {
namespace mbc {
class MBC3 : public MemoryBankController {
 public:
    MBC3(uint8_t **romBanks, uint8_t numBanks);
    virtual uint8_t* getCurrentROMBank();
    virtual void write(uint16_t address, uint8_t value);

 private:
    uint16_t currentROMBank;
};
}
}

#endif