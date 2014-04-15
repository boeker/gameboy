// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_MBC_MBC1RAM_H
#define GAMEBOY_MBC_MBC1RAM_H

#include <cinttypes>

#include "mbc1.h"

namespace gameboy {
namespace mbc {
class MBC1RAM : public MBC1 {
 public:
    MBC1RAM(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length);
    virtual ~MBC1RAM();
    virtual void write(uint16_t address, uint8_t value);

    virtual void writeRAM(uint16_t address, uint8_t value);
    virtual uint8_t readRAM(uint16_t address);

 protected:
    uint8_t **ramBanks;
    uint8_t numOfRAMBanks;
    uint16_t ramLength;

 private:
    uint16_t currentRAMBank;
    bool ramBanking;
    bool enabled;
};
}
}

#endif