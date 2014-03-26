#ifndef GAMEBOY_MBC_MBC5RAM_H
#define GAMEBOY_MBC_MBC5RAM_H

#include <cinttypes>

#include "mbc5.h"

namespace gameboy {
namespace mbc {
class MBC5RAM : public MBC5 {
 public:
    MBC5RAM(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length);
    virtual ~MBC5RAM();
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
};
}
}

#endif