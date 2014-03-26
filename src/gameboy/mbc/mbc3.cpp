#include "mbc3.h"

namespace gameboy {
namespace mbc {
MBC3::MBC3(uint8_t **romBanks, uint8_t numBanks) :
    MemoryBankController(romBanks, numBanks),
    currentROMBank(1) {
}

uint8_t* MBC3::getCurrentROMBank() {
    return romBanks[currentROMBank];
}

void MBC3::write(uint16_t address, uint8_t value) {
    if (address >= 0x2000 && address <= 0x3FFF) { // 7 Bits of ROM Bank Number
        currentROMBank = value & 0x7F;
    }

    if (currentROMBank == 0x00) {
        currentROMBank++;
    }
}
}
}