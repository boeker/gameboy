// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_MBC_MBC5RAMBATT_H
#define GAMEBOY_MBC_MBC5RAMBATT_H

#include <cinttypes>
#include <string>

#include "mbc5ram.h"

namespace gameboy {
namespace mbc {
class MBC5RAMBATT : public MBC5RAM {
 public:
    MBC5RAMBATT(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& save);
    virtual ~MBC5RAMBATT();
 private:
    const std::string saveFile;
};
}
}

#endif