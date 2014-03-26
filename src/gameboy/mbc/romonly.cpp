#include "romonly.h"

namespace gameboy {
namespace mbc {
ROMOnly::ROMOnly(uint8_t **romBanks, uint8_t numBanks) :
    MemoryBankController(romBanks, numBanks) {
}

uint8_t* ROMOnly::getCurrentROMBank() {
    return romBanks[1];
}

void ROMOnly::write(uint16_t, uint8_t) {
}
}
}