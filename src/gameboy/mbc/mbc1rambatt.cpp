#include "mbc1rambatt.h"

#include "memorybankcontroller.h"
#include <QDebug>

namespace gameboy {
namespace mbc {
MBC1RAMBATT::MBC1RAMBATT(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& save) :
    MBC1RAM(romBanks, numBanks, ramBanks, numRam, length),
    saveFile(save) {
    MemoryBankController::readSave(ramBanks, numOfRAMBanks, ramLength, saveFile);
}

MBC1RAMBATT::~MBC1RAMBATT() {
    MemoryBankController::writeSave(ramBanks, numOfRAMBanks, ramLength, saveFile);
}
}
}