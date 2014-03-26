#ifndef GAMEBOY_MBC_MBC1RAMBATT_H
#define GAMEBOY_MBC_MBC1RAMBATT_H

#include <cinttypes>
#include <string>

#include "mbc1ram.h"

namespace gameboy {
namespace mbc {
class MBC1RAMBATT : public MBC1RAM {
 public:
    MBC1RAMBATT(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& save);
    virtual ~MBC1RAMBATT();
 private:
    const std::string saveFile;
};
}
}

#endif