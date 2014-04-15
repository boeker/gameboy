// Copyright (c) 2014 Jan Böker
// MIT License

#include "memorybankcontroller.h"

#include <QDebug>
#include <fstream>

namespace gameboy {
namespace mbc {
MemoryBankController::MemoryBankController(uint8_t **romBanks, uint8_t numBanks) :
    romBanks(romBanks),
    numOfROMBanks(numBanks) {
}

MemoryBankController::~MemoryBankController() {
    for (int i = 0; i < numOfROMBanks; ++i) {
        delete[] romBanks[i];
    }
    delete[] romBanks;
}

void MemoryBankController::writeRAM(uint16_t address, uint8_t value) {
    qDebug() << "Warning: writeRAM() on non-RAM MBC, " << value << "@" << address;
}

uint8_t MemoryBankController::readRAM(uint16_t) {
    qDebug() << "Warning: readRAM() on non-RAM MBC";
    return 0;
}

void MemoryBankController::readSave(uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& saveFile) {
    std::ifstream save(saveFile, std::ios::binary);
    if (save.good()) {
        for (int i = 0; i < numRam; ++i) {
            save.read(reinterpret_cast<char*>(ramBanks[i]), length);
        }
    }
}

void MemoryBankController::writeSave(uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& saveFile) {
    std::ofstream save(saveFile, std::ios::binary);
    for (int i = 0; i < numRam; ++i) {
        save.write(reinterpret_cast<const char*>(ramBanks[i]), length);
    }
}
}
}