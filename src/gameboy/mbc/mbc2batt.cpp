// Copyright (c) 2014 Jan Böker
// MIT License

#include "mbc2batt.h"

#include "memorybankcontroller.h"
#include <QDebug>

namespace gameboy {
namespace mbc {
MBC2BATT::MBC2BATT(uint8_t **romBanks, uint8_t numBanks, const std::string& save) :
    MBC2(romBanks, numBanks),
    saveFile(save) {
    MemoryBankController::readSave(ram, 1, 512, saveFile);
}

MBC2BATT::~MBC2BATT() {
    MemoryBankController::writeSave(ram, 1, 512, saveFile);
}
}
}