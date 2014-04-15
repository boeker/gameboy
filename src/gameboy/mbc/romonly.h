// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_MBC_ROMONLY_H
#define GAMEBOY_MBC_ROMONLY_H

#include <cinttypes>

#include "memorybankcontroller.h"

namespace gameboy {
namespace mbc {
class ROMOnly : public MemoryBankController {
 public:
    ROMOnly(uint8_t **romBanks, uint8_t numBanks);
    virtual uint8_t* getCurrentROMBank();
    virtual void write(uint16_t, uint8_t);
};
}
}

#endif