#ifndef GAMEBOY_MBC_MBC3RAM_H
#define GAMEBOY_MBC_MBC3RAM_H

#include <cinttypes>

#include "mbc3.h"

namespace gameboy {
namespace mbc {
class MBC3RAM : public MBC3 {
 public:
    MBC3RAM(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length);
    virtual ~MBC3RAM();
    virtual void write(uint16_t address, uint8_t value);

    virtual void writeRAM(uint16_t address, uint8_t value);
    virtual uint8_t readRAM(uint16_t address);

 protected:
    uint8_t **ramBanks;
    uint8_t numOfRAMBanks;
    uint16_t ramLength;

 private:
    uint16_t currentRAMBank;
    bool enabled;
};
}
}

#endif