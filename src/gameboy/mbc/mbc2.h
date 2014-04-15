// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_MBC_MBC2_H
#define GAMEBOY_MBC_MBC2_H

#include <cinttypes>

#include "memorybankcontroller.h"

namespace gameboy {
namespace mbc {
class MBC2 : public MemoryBankController {
 public:
    MBC2(uint8_t **romBanks, uint8_t numBanks);
    virtual ~MBC2();
    virtual uint8_t* getCurrentROMBank();
    virtual void write(uint16_t address, uint8_t value);

    virtual void writeRAM(uint16_t address, uint8_t value);
    virtual uint8_t readRAM(uint16_t address);

 protected:
    uint8_t **ram;

 private:
    uint16_t currentROMBank;
    bool enabled;
};
}
}

#endif