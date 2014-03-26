#include "mbc1.h"

namespace gameboy {
namespace mbc {
MBC1::MBC1(uint8_t **romBanks, uint8_t numBanks) :
    MemoryBankController(romBanks, numBanks),
    currentROMBank(1) {
}

uint8_t* MBC1::getCurrentROMBank() {
    return romBanks[currentROMBank];
}

void MBC1::write(uint16_t address, uint8_t value) {
    if (address >= 0x2000 && address <= 0x3FFF) { // Lower 5 Bits of ROM Bank Number
        uint8_t lowerFiveBits = value & 0x1F;

        currentROMBank = (currentROMBank & 0xE0) | lowerFiveBits;
    } else if (address >= 0x4000 && address <= 0x5FFF) { // Upper 2 Bits of ROM Bank Number
        uint8_t upperTwoBits = value & 0x03;

        currentROMBank = (currentROMBank & 0x1F) | (upperTwoBits << 5);
    }

    if (currentROMBank == 0x00
        || currentROMBank == 0x20
        || currentROMBank == 0x40
        || currentROMBank == 0x60) {
        currentROMBank++;
    }
}
}
}