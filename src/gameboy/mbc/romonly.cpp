#include "romonly.h"

namespace gameboy {
namespace mbc {
ROMOnly::ROMOnly(uint8_t *romBank) :
    romBank(romBank) {
        ram = new uint8_t[8192];
}

ROMOnly::~ROMOnly() {
    delete[] ram;
}

uint8_t* ROMOnly::getExternalRAM() {
    return ram;
}

uint8_t* ROMOnly::getROMBank() {
    return romBank;
}

void ROMOnly::write(uint16_t, uint8_t) {
}
}
}