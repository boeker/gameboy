#include "mbc1ram.h"

namespace gameboy {
namespace mbc {
MBC1RAM::MBC1RAM(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length) :
    MBC1(romBanks, numBanks),
    ramBanks(ramBanks),
    numOfRAMBanks(numRam),
    ramLength(length),
    currentRAMBank(0),
    ramBanking(false) {
}

MBC1RAM::~MBC1RAM() {
    for (int i = 0; i < numOfRAMBanks; ++i) {
        delete[] ramBanks[i];
    }
    delete[] ramBanks;
}

void MBC1RAM::write(uint16_t address, uint8_t value) {
    if (address >= 0x6000 && address <= 0x7FFF) { // ROM/RAM Mode Select
        ramBanking = value;
    } else if (ramBanking && address >= 0x4000 && address <= 0x5FFF) {
        // Upper 2 Bits of ROM Bank Number or RAM Bank Number
        currentRAMBank = value & 0x03;
    } else {
        MBC1::write(address, value);
    }
}

void MBC1RAM::writeRAM(uint16_t address, uint8_t value) {
    ramBanks[currentRAMBank][address] = value;
}

uint8_t MBC1RAM::readRAM(uint16_t address) {
    return ramBanks[currentRAMBank][address];
}
}
}