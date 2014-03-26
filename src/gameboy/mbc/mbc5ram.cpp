#include "mbc5ram.h"

namespace gameboy {
namespace mbc {
MBC5RAM::MBC5RAM(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length) :
    MBC5(romBanks, numBanks),
    ramBanks(ramBanks),
    numOfRAMBanks(numRam),
    ramLength(length),
    currentRAMBank(0),
    ramBanking(false),
    enabled(false) {
}

MBC5RAM::~MBC5RAM() {
    for (int i = 0; i < numOfRAMBanks; ++i) {
        delete[] ramBanks[i];
    }
    delete[] ramBanks;
}

void MBC5RAM::write(uint16_t address, uint8_t value) {
    if (address <= 0x1FFF) {
        enabled = value;
    } else if (address >= 0x4000 && address <= 0x5FFF) { // RAM Bank Number
        currentRAMBank = value & 0x0F;
    } else {
        MBC5::write(address, value);
    }
}

void MBC5RAM::writeRAM(uint16_t address, uint8_t value) {
    if (enabled) {
        ramBanks[currentRAMBank][address] = value;
    }
}

uint8_t MBC5RAM::readRAM(uint16_t address) {
    return enabled ? ramBanks[currentRAMBank][address] : 0;
}
}
}