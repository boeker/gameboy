// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_MBC_MBC3RAMBATT_H
#define GAMEBOY_MBC_MBC3RAMBATT_H

#include <cinttypes>
#include <string>

#include "mbc3ram.h"

namespace gameboy {
namespace mbc {
class MBC3RAMBATT : public MBC3RAM {
 public:
    MBC3RAMBATT(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& save);
    virtual ~MBC3RAMBATT();
 private:
    const std::string saveFile;
};
}
}

#endif