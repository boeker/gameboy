#include "mbc5rambatt.h"

#include "memorybankcontroller.h"
#include <QDebug>

namespace gameboy {
namespace mbc {
MBC5RAMBATT::MBC5RAMBATT(uint8_t **romBanks, uint8_t numBanks, uint8_t **ramBanks, uint8_t numRam, uint16_t length, const std::string& save) :
    MBC5RAM(romBanks, numBanks, ramBanks, numRam, length),
    saveFile(save) {
    MemoryBankController::readSave(ramBanks, numOfRAMBanks, ramLength, saveFile);
}

MBC5RAMBATT::~MBC5RAMBATT() {
    MemoryBankController::writeSave(ramBanks, numOfRAMBanks, ramLength, saveFile);
}
}
}