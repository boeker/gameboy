// Copyright (c) 2014 Jan Böker
// MIT License

#include "mbc5.h"

namespace gameboy {
namespace mbc {
MBC5::MBC5(uint8_t **romBanks, uint8_t numBanks) :
    MemoryBankController(romBanks, numBanks),
    currentROMBank(1) {
}

uint8_t* MBC5::getCurrentROMBank() {
    return romBanks[currentROMBank];
}

void MBC5::write(uint16_t address, uint8_t value) {
    if (address >= 0x2000 && address <= 0x2FFF) { // Low 8 bits of ROM Bank Number 

        currentROMBank = (currentROMBank & 0xFF00) | value;
    } else if (address >= 0x3000 && address <= 0x3FFF) { // High bit of ROM Bank Number
        uint8_t upperBit = value & 0x01;

        currentROMBank = (currentROMBank & 0x00FF) | (upperBit << 8);
    }
}
}
}