#include "mbc3tim.h"

#include <QDebug>
#include <cstring>
#include <ctime>

namespace gameboy {
namespace mbc {
MBC3TIM::MBC3TIM(uint8_t **romBanks, uint8_t numBanks) :
    MBC3(romBanks, numBanks),
    enabled(false),
    timEnabled(false),
    currentRegister(0) {
        rtcRegisters = new uint8_t[5];
        memset(rtcRegisters, 0, 5);
}

MBC3TIM::~MBC3TIM() {
    delete[] rtcRegisters;
}

void MBC3TIM::write(uint16_t address, uint8_t value) {
    if (address <= 0x1FFF) {
        enabled = (value & 0x0A) == 0x0A;
    } else if (address >= 0x4000 && address <= 0x5FFF) {
        // Map RTC register
        currentRegister = value - 0x08;
    } else if (address >= 0x6000 && address <= 0x7FFF) { // Latch Clock Data
        // 00 -> 01 => Latch current time into the RTC registers
        time_t currentTime = time(0);
        struct tm* localTime = localtime(&currentTime);
        rtcRegisters[0] = localTime->tm_sec % 60;
        rtcRegisters[1] = localTime->tm_min;
        rtcRegisters[2] = localTime->tm_hour; 
        rtcRegisters[4] = 0; // TODO - Has to be written to a file
        rtcRegisters[5] = 0; 
    } else {
        MBC3::write(address, value);
    }
}

void MBC3TIM::writeRAM(uint16_t, uint8_t value) {
    if (enabled && currentRegister <= 5) {
        rtcRegisters[currentRegister] = value;
    }
}

uint8_t MBC3TIM::readRAM(uint16_t) {
    return (enabled && currentRegister <= 5) ? rtcRegisters[currentRegister] : 0;
}
}
}