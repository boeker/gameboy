// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_MBC_MBC2BATT_H
#define GAMEBOY_MBC_MBC2BATT_H

#include <cinttypes>
#include <string>

#include "mbc2.h"

namespace gameboy {
namespace mbc {
class MBC2BATT : public MBC2 {
 public:
    MBC2BATT(uint8_t **romBanks, uint8_t numBanks, const std::string& save);
    virtual ~MBC2BATT();
 private:
    const std::string saveFile;
};
}
}

#endif