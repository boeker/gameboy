#ifndef GAMEBOY_MBC_MBC3TIMRAMBATT_H
#define GAMEBOY_MBC_MBC3TIMRAMBATT_H

#include <cinttypes>

#include "mbc3tim.h"

namespace gameboy {
namespace mbc {
class MBC3TIMRAMBATT : public MBC3TIM {
 public:
    MBC3TIMRAMBATT(uint8_t **romBanks, uint8_t numBanks, const std::string& rtc, uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& save);
    virtual ~MBC3TIMRAMBATT();
    virtual void write(uint16_t address, uint8_t value);

    virtual void writeRAM(uint16_t address, uint8_t value);
    virtual uint8_t readRAM(uint16_t address);

 protected:
    uint8_t **ramBanks;
    uint8_t numOfRAMBanks;
    uint16_t ramLength;

 private:
    uint16_t currentRAMBank;
    bool ramEnabled;
    const std::string saveFile;
};
}
}

#endif