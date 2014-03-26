#ifndef GAMEBOY_MBC_MBC3TIM_H
#define GAMEBOY_MBC_MBC3TIM_H

#include <cinttypes>

#include "mbc3.h"

namespace gameboy {
namespace mbc {
class MBC3TIM : public MBC3 {
 public:
    MBC3TIM(uint8_t **romBanks, uint8_t numBanks);
    virtual ~MBC3TIM();
    virtual void write(uint16_t address, uint8_t value);

    virtual void writeRAM(uint16_t, uint8_t value);
    virtual uint8_t readRAM(uint16_t);

 protected:
    bool enabled;

 private:
    bool timEnabled;
    uint8_t *rtcRegisters;
    uint8_t currentRegister;
    // RTC S Seconds 0-59
    // RTC M Minutes 0-59
    // RTC H Hours 0-23
    // RTC DL Lower 8 bits of Day Counter 0-255
    // RTC DH Upper 1 bit of Day Counter (Bit 0)
        // Halt Flag (Bit 6, 0 = Active, 1 = Stop Timer)
        // Day Counter Carry (Bit 7, 1 = Counter Overflow)
};
}
}

#endif