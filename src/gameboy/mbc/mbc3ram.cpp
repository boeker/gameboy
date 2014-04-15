// Copyright (c) 2014 Jan Böker
// MIT License

#include "mbc3ram.h"

namespace gameboy {
namespace mbc {
MBC3RAM::MBC3RAM(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length) :
    MBC3(romBanks, numBanks),
    ramBanks(ramBanks),
    numOfRAMBanks(numRam),
    ramLength(length),
    currentRAMBank(0),
    enabled(false) {
}

MBC3RAM::~MBC3RAM() {
    for (int i = 0; i < numOfRAMBanks; ++i) {
        delete[] ramBanks[i];
    }
    delete[] ramBanks;
}

void MBC3RAM::write(uint16_t address, uint8_t value) {
    if (address <= 0x1FFF) {
        enabled = (value & 0x0A) == 0x0A;
    } else if (address >= 0x4000 && address <= 0x5FFF) {
        // Upper 2 Bits of ROM Bank Number or RAM Bank Number
        currentRAMBank = value & 0x03;
    } else {
        MBC3::write(address, value);
    }
}

void MBC3RAM::writeRAM(uint16_t address, uint8_t value) {
    if (enabled) {
        ramBanks[currentRAMBank][address] = value;
    }
}

uint8_t MBC3RAM::readRAM(uint16_t address) {
    return enabled ? ramBanks[currentRAMBank][address] : 0;
}
}
}