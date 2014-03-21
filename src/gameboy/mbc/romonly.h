#ifndef GAMEBOY_MBC_ROMONLY_H
#define GAMEBOY_MBC_ROMONLY_H

#include <cinttypes>

#include "memorybankcontroller.h"

namespace gameboy {
namespace mbc {
class ROMOnly : public MemoryBankController {
 public:
    ROMOnly(uint8_t *romBank);
    virtual ~ROMOnly();
    virtual uint8_t* getExternalRAM();
    virtual uint8_t* getROMBank();
    virtual void write(uint16_t, uint8_t);

 private:
    uint8_t *romBank;
    uint8_t *ram;
};
}
}

#endif