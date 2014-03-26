/*#include "mbc5ram.h"

namespace gameboy {
namespace mbc {
MBC5RAM::MBC5RAM(uint8_t **romBanks, uint8_t num, uint8_t **ramBanks, uint8_t numRam) :
    romBanks(romBanks),
    numOfROMBanks(num),
    currentROMBank(0),
    ramBanks(ramBanks),
    numOfRAMBanks(numRam),
    currentRAMBank(0),
    ramBanking(false) {
}

MBC5RAM::~MBC5RAM() {
    for (int i = 0; i < numOfROMBanks; ++i) {
        delete[] romBanks[i];
    }
    delete[] romBanks;

    for (int i = 0; i < numOfRAMBanks; ++i) {
        delete[] ramBanks[i];
    }
    delete[] ramBanks;
}

uint8_t* MBC5RAM::getExternalRAM() {
    return ramBanks[currentRAMBank];
}

uint8_t* MBC5RAM::getROMBank() {
    return romBanks[currentROMBank-1];
}

void MBC5RAM::write(uint16_t address, uint8_t value) {
    if (address >= 0x2000 && address <= 0x2FFF) { // Low 8 bits of ROM Bank Number 

        currentROMBank = (currentROMBank & 0xFF00) | value;
    } else if (address >= 0x3000 && address <= 0x3FFF) { // High bit of ROM Bank Number
        uint8_t upperBit = value & 0x01;

        currentROMBank = (currentROMBank & 0x00FF) | (upperBit << 8);
    } else if (address >= 0x4000 && address <= 0x5FFF) { // RAM Bank Number
        currentRAMBank = value & 0x0F;
    }
}
}
}*/