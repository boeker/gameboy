// Copyright (c) 2014 Jan Böker
// MIT License

#include "mbc2.h"

namespace gameboy {
namespace mbc {
MBC2::MBC2(uint8_t **romBanks, uint8_t numBanks) :
    MemoryBankController(romBanks, numBanks),
    currentROMBank(1) {
        ram = new uint8_t*[1];
        ram[0] = new uint8_t[512];
}

MBC2::~MBC2() {
    delete ram;
}

uint8_t* MBC2::getCurrentROMBank() {
    return romBanks[currentROMBank];
}

void MBC2::write(uint16_t address, uint8_t value) {
    if (address <= 0x1FFF) { // RAM Enable
        if ((address & 0x0100) == 0) {
            enabled = (value & 0x0A) == 0x0A;
        }
    } else if (address >= 0x2000 && address <= 0x3FFF) { // ROM Bank Number
        if (address & 0x0100) {
            currentROMBank = value & 0x0F;
        }
    }
}

void MBC2::writeRAM(uint16_t address, uint8_t value) {
    if (enabled) {
        ram[0][address] = value & 0x0F;
    }
}

uint8_t MBC2::readRAM(uint16_t address) {
    return enabled ? (ram[0][address] & 0x0F) : 0;
}
}
}