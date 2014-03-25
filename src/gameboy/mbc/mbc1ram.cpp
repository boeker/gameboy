#include "mbc1ram.h"

namespace gameboy {
namespace mbc {
MBC1RAM::MBC1RAM(uint8_t **romBanks, uint8_t num, uint8_t **ramBanks, uint8_t numRam) :
    romBanks(romBanks),
    numOfROMBanks(num),
    currentROMBank(1),
    ramBanks(ramBanks),
    numOfRAMBanks(numRam),
    currentRAMBank(0),
    ramBanking(false) {
}

MBC1RAM::~MBC1RAM() {
    for (int i = 0; i < numOfROMBanks; ++i) {
        delete[] romBanks[i];
    }
    delete[] romBanks;

    for (int i = 0; i < numOfRAMBanks; ++i) {
        delete[] ramBanks[i];
    }
    delete[] ramBanks;
}

uint8_t* MBC1RAM::getExternalRAM() {
    return ramBanks[currentRAMBank];
}

uint8_t* MBC1RAM::getROMBank() {
    return romBanks[currentROMBank-1];
}

void MBC1RAM::write(uint16_t address, uint8_t value) {
    if (address >= 0x2000 && address <= 0x3FFF) { // Lower 5 Bits of ROM Bank Number
        uint8_t lowerFiveBits = value & 0x1F;

        currentROMBank = (currentROMBank & 0xE0) | lowerFiveBits;
    } else if (address >= 0x4000 && address <= 0x5FFF) {
        uint8_t upperTwoBits = value & 0x03;

        // Upper 2 Bits of ROM Bank Number or RAM Bank Number
        if (ramBanking) {
            currentRAMBank = upperTwoBits;
        } else {
            currentROMBank = (currentROMBank & 0x1F) | (upperTwoBits << 5);
        }
    } else if (address >= 0x6000 && address <= 0x7FFF) { // ROM/RAM Mode Select
        ramBanking = value;
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