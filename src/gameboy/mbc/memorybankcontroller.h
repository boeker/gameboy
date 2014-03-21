#ifndef GAMEBOY_MBC_MEMORYBANKCONTROLLER_H
#define GAMEBOY_MBC_MEMORYBANKCONTROLLER_H

#include <cinttypes>

namespace gameboy {
namespace mbc {
class MemoryBankController {
 public:
    virtual ~MemoryBankController() {};
    virtual uint8_t* getExternalRAM() = 0;
    virtual uint8_t* getROMBank() = 0;
    virtual void write(uint16_t address, uint8_t value) = 0;
};
}
}

#endif