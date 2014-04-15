// Copyright (c) 2014 Jan Böker
// MIT License

#include "mbc3rambatt.h"

#include "memorybankcontroller.h"
#include <QDebug>

namespace gameboy {
namespace mbc {
MBC3RAMBATT::MBC3RAMBATT(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& save) :
    MBC3RAM(romBanks, numBanks, ramBanks, numRam, length),
    saveFile(save) {
    MemoryBankController::readSave(ramBanks, numOfRAMBanks, ramLength, saveFile);
}

MBC3RAMBATT::~MBC3RAMBATT() {
    MemoryBankController::writeSave(ramBanks, numOfRAMBanks, ramLength, saveFile);
}
}
}