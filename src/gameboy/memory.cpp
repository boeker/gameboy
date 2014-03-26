#include "memory.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <QDebug>
#include "mbc/memorybankcontroller.h"
#include "mbc/romonly.h"
#include "mbc/mbc1.h"
#include "mbc/mbc1ram.h"
#include "mbc/mbc1rambatt.h"
#include "mbc/mbc3.h"
#include "mbc/mbc3ram.h"
#include "mbc/mbc3rambatt.h"
#include "mbc/mbc3tim.h"
#include "mbc/mbc3timrambatt.h"
#include "mbc/mbc5.h"
#include "mbc/mbc5ram.h"
#include "mbc/mbc5rambatt.h"

namespace gameboy {
Memory::Memory() {
    ieReg = new uint8_t;
    highRam = new uint8_t[127];
    ioPorts = new uint8_t[224];
    spriteAttTab = new uint8_t[160];
    internalRam = new uint8_t[8192];
    videoRam = new uint8_t[8192];
    mbc = 0;

    reset();
}

Memory::~Memory() {
    delete ieReg;
    delete[] highRam;
    delete[] ioPorts;
    delete[] spriteAttTab;
    delete[] internalRam;
    delete[] videoRam;

    if (mbc) {
        delete mbc;
    }
}

void Memory::reset() {
    *ieReg = 0;
    memset(highRam, 0, 127);
    memset(ioPorts, 0, 224);
    memset(spriteAttTab, 0, 160);
    memset(internalRam, 0, 8192);
    memset(videoRam, 0, 8192);

    writeRaw(0xFF05, 0x00);
    writeRaw(0xFF06, 0x00);
    writeRaw(0xFF07, 0x00);
    writeRaw(0xFF10, 0x80);
    writeRaw(0xFF11, 0xBF);
    writeRaw(0xFF12, 0xF3);
    writeRaw(0xFF14, 0xBF);
    writeRaw(0xFF16, 0x3F);
    writeRaw(0xFF17, 0x00);
    writeRaw(0xFF19, 0xBF);
    writeRaw(0xFF1A, 0x7F);
    writeRaw(0xFF1B, 0xFF);
    writeRaw(0xFF1C, 0x9F);
    writeRaw(0xFF1E, 0xBF);
    writeRaw(0xFF20, 0xFF);
    writeRaw(0xFF21, 0x00);
    writeRaw(0xFF22, 0x00);
    writeRaw(0xFF23, 0xBF);
    writeRaw(0xFF24, 0x77);
    writeRaw(0xFF25, 0xF3);
    writeRaw(0xFF26, 0xF1);
    writeRaw(0xFF40, 0x91);
    writeRaw(0xFF42, 0x00);
    writeRaw(0xFF43, 0x00);
    writeRaw(0xFF45, 0x00);
    writeRaw(0xFF47, 0xFC);
    writeRaw(0xFF48, 0xFF);
    writeRaw(0xFF49, 0xFF);
    writeRaw(0xFF4A, 0x00);
    writeRaw(0xFF4B, 0x00);
    writeRaw(0xFFFF, 0x00);

    if (mbc) {
        delete mbc;
        mbc = 0;
    }
}

void Memory::loadROM(const std::string &file) {
    rom = new uint8_t[16384];

    std::ifstream cartridge(file.c_str(), std::ios::binary);
    if (!cartridge.good()) {
        exit(1);
    }
    cartridge.read(reinterpret_cast<char*>(rom), 16384);

    uint8_t romSize = rom[0x0148];
    uint16_t numBanks;
    switch (romSize) {
        case 0x52:
            numBanks = 72;
        break;
        case 0x53:
            numBanks = 80;
        break;
        case 0x54:
            numBanks = 96;
        break;
        default:
            numBanks = pow(2, romSize+1);
        break;
    }

    uint8_t** romBanks = new uint8_t*[numBanks];
    romBanks[0] = rom;
    for (int i = 1; i < numBanks; ++i) {
        romBanks[i] = new uint8_t[16384];
        cartridge.read(reinterpret_cast<char*>(romBanks[i]), 16384);
    }

    uint8_t ramSize = rom[0x0149];
    uint8_t numRamBanks;
    uint8_t** ramBanks;
    uint16_t ramLength = 0;
    switch (ramSize) {
        case 0x01:
            ramLength = 2048;
            numRamBanks = 1;
            ramBanks = new uint8_t*[numRamBanks];
            ramBanks[0] = new uint8_t[ramLength];
            memset(ramBanks[0], 0, ramLength);
        break;
        case 0x02:
            ramLength = 8192;
            numRamBanks = 1;
            ramBanks = new uint8_t*[numRamBanks];
            ramBanks[0] = new uint8_t[ramLength];
            memset(ramBanks[0], 0, ramLength);
        break;
        case 0x03:
            ramLength = 8192;
            numRamBanks = 4;
            ramBanks = new uint8_t*[numRamBanks];
            for (int i = 0; i < numRamBanks; ++i) {
                ramBanks[i] = new uint8_t[ramLength];
                memset(ramBanks[i], 0, ramLength);
            }
        break;
        default:
            numRamBanks = 0;
            ramBanks = 0;
        break;
    }

    std::string saveFile = file.substr(0, file.find_last_of('.')) + ".sav";

    uint8_t cartridgeType = rom[0x0147];
    switch (cartridgeType) {
        case 0x00: // ROM only
            mbc = new mbc::ROMOnly(romBanks, numBanks);
        break;
        case 0x01: // MBC1
            mbc = new mbc::MBC1(romBanks, numBanks);
        break;
        case 0x02: // MBC1 + RAM
            mbc = new mbc::MBC1RAM(romBanks, numBanks, ramBanks, numRamBanks, ramLength);
        break;
        case 0x03: // MBC1 + RAM + BATTERY
            mbc = new mbc::MBC1RAMBATT(romBanks, numBanks, ramBanks, numRamBanks, ramLength, saveFile);
        break;
        case 0x19: // MBC5
            mbc = new mbc::MBC5(romBanks, numBanks);
        break;
        case 0x1A: // MBC5 + RAM
            mbc = new mbc::MBC5RAM(romBanks, numBanks, ramBanks, numRamBanks, ramLength);
        break;
        case 0x1B: // MBC5 + RAM + BATTERY
            mbc = new mbc::MBC5RAMBATT(romBanks, numBanks, ramBanks, numRamBanks, ramLength, saveFile);
        break;
        case 0x1C: // MBC5 + RUMBLE
            mbc = new mbc::MBC5(romBanks, numBanks);
        break;
        case 0x1D: // MBC5 + RUMBLE + RAM
            mbc = new mbc::MBC5RAM(romBanks, numBanks, ramBanks, numRamBanks, ramLength);
        break;
        case 0x1E: // MBC5 + RUMBLE + RAM + BATTERY
            mbc = new mbc::MBC5RAMBATT(romBanks, numBanks, ramBanks, numRamBanks, ramLength, saveFile);
        break;
        case 0x0F: // MBC3 + TIMER + BATTERY
            mbc = new mbc::MBC3TIM(romBanks, numBanks);
        break;
        case 0x10: // MBC3 + TIMER + RAM + BATTERY
            mbc = new mbc::MBC3TIMRAMBATT(romBanks, numBanks, ramBanks, numRamBanks, ramLength, saveFile);
        break;
        case 0x11: // MBC3
            mbc = new mbc::MBC3(romBanks, numBanks);
        break;
        case 0x12: // MBC3 + RAM
            mbc = new mbc::MBC3RAM(romBanks, numBanks, ramBanks, numRamBanks, ramLength);
        break;
        case 0x13: // MBC3 + RAM + BATTERY
            mbc = new mbc::MBC3RAMBATT(romBanks, numBanks, ramBanks, numRamBanks, ramLength, saveFile);
        break;
        default:
            qDebug() << "Unknown cartridge type " << cartridgeType;
            exit(1);
        break;
    }

    romBank = mbc->getCurrentROMBank();
}

uint8_t Memory::read(uint16_t address) {
    if ((address >= 0xA000) && (address <= 0xBFFF)) {
        return mbc->readRAM(address - 0xA000);
    } else {
        uint8_t *memLoc = resolveAddress(address);
        return *memLoc;
    }
}

void Memory::write(uint16_t address, uint8_t value) {
    if (address <= 0x7FFF) { // Write to ROM
        mbc->write(address, value);
        romBank = mbc->getCurrentROMBank();
    } else if ((address >= 0xA000) && (address <= 0xBFFF)) {
        mbc->writeRAM(address - 0xA000, value);
    } else {
        uint8_t *memLoc = resolveAddress(address);
        *memLoc = value;

        // FF46 - DMA - DMA Transfer and Start Address (W)
        if (address == 0xFF46) {
            uint16_t startAddr = read(0xFF46) * 0x100;
            for (int i = 0; i < 160; ++i) {
                write(0xFE00+i, read(startAddr+i));
            }
        }
        // FF04 - Divider Timer - Resets to 0 whenever written to
        if (address == 0xFF04) {
            *memLoc = 0;
        }
    }
}

void Memory::writeRaw(uint16_t address, uint8_t value) {
    if ((address >= 0xA000) && (address <= 0xBFFF)) {
        mbc->writeRAM(address - 0xA000, value);
    } else {
        uint8_t *memLoc = resolveAddress(address);
        *memLoc = value;
    }
}

uint16_t Memory::readW(uint16_t address) {
    return (read(address+1) << 8) | read(address);
}

void Memory::writeW(uint16_t address, uint16_t value) {
    write(address, value & 0x00FF);
    write(address+1, (value & 0xFF00) >> 8);
}

uint8_t* Memory::resolveAddress(uint16_t address) {
    if (address <= 0x3FFF) {
        return rom + address;
    }
    if ((address >= 0x4000) && (address <= 0x7FFF)) {
        return romBank + address - 0x4000;
    }
    if ((address >= 0x8000) && (address <= 0x9FFF)) {
        return videoRam + address - 0x8000;
    }
    // External RAM
    if ((address >= 0xC000) && (address <= 0xDFFF)) {
        return internalRam + address - 0xC000;
    }
    if ((address >= 0xE000) && (address <= 0xFDFF)) {
        return internalRam + address - 0xE000;
    }
    if ((address >= 0xFE00) && (address <= 0xFE9F)) {
        return spriteAttTab + address - 0xFE00;
    }
    if ((address >= 0xFEA0) && (address <= 0xFF7F)) {
        return ioPorts + address - 0xFEA0;
    }
    if ((address >= 0xFF80) && (address <= 0xFFFE)) {
        return highRam + address - 0xFF80;
    }
    if (address == 0xFFFF) {
        return ieReg;
    }
    return 0;  // Will never happen, I swear
}
}
