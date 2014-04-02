#include "mbc3timrambatt.h"

namespace gameboy {
namespace mbc {
MBC3TIMRAMBATT::MBC3TIMRAMBATT(uint8_t **romBanks, uint8_t numBanks, const std::string& rtc, uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& save) :
    MBC3TIM(romBanks, numBanks, rtc),
    ramBanks(ramBanks),
    numOfRAMBanks(numRam),
    ramLength(length),
    currentRAMBank(0),
    ramEnabled(false),
    saveFile(save) {
        MemoryBankController::readSave(ramBanks, numOfRAMBanks, ramLength, saveFile);
}

MBC3TIMRAMBATT::~MBC3TIMRAMBATT() {
    MemoryBankController::writeSave(ramBanks, numOfRAMBanks, ramLength, saveFile);

    for (int i = 0; i < numOfRAMBanks; ++i) {
        delete[] ramBanks[i];
    }
    delete[] ramBanks;
}

void MBC3TIMRAMBATT::write(uint16_t address, uint8_t value) {
    if (address >= 0x4000 && address <= 0x5FFF && value <= 3) {
        // RAM Bank Number
        currentRAMBank = value & 0x03;
        ramEnabled = true;
    } else if (address >= 0x4000 && address <= 0x5FFF) {
        ramEnabled = false;
        MBC3TIM::write(address, value);
    } else {
        MBC3TIM::write(address, value);
    }
}

void MBC3TIMRAMBATT::writeRAM(uint16_t address, uint8_t value) {
    if (enabled) {
        if (ramEnabled) {
            ramBanks[currentRAMBank][address] = value;
        } else {
            MBC3TIM::writeRAM(address, value);
        }
    }
}

uint8_t MBC3TIMRAMBATT::readRAM(uint16_t address) {
    if (enabled) {
        if (ramEnabled) {
            return ramBanks[currentRAMBank][address];
        } else {
            return MBC3TIM::readRAM(address);
        }
    } else {
        return 0;
    }
}
}
}