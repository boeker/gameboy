#include "memory.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>

namespace gameboy {
Memory::Memory(const std::string &file) :
    selectedAddBank(0) {
    ieReg = new uint8_t;
    highRam = new uint8_t[127];
    ioPorts = new uint8_t[224];
    spriteAttTab = new uint8_t[160];
    internalRam = new uint8_t[8192];
    externalRam = new uint8_t[8192];
    videoRam = new uint8_t[8192];
    romBank0 = new uint8_t[16384];

    memset(ieReg, 0, 1);  // Yeah, I know...
    memset(highRam, 0, 127);
    memset(ioPorts, 0, 224);
    memset(spriteAttTab, 0, 160);
    memset(internalRam, 0, 8192);
    memset(externalRam, 0, 8192);
    memset(videoRam, 0, 8192);
    memset(romBank0, 0, 16384);


    std::ifstream cartridge(file.c_str(), std::ios::binary);
    if (!cartridge.good()) {
        exit(1);
    }
    cartridge.read(reinterpret_cast<char*>(romBank0), 16384);
    int romSize = romBank0[0x0148];
    switch (romSize) {
        case 0x52:
            numOfAddBanks = 72-1;
        break;
        case 0x53:
            numOfAddBanks = 80-1;
        break;
        case 0x54:
            numOfAddBanks = 96-1;
        break;
        default:
            numOfAddBanks = pow(2, romSize+1)-1;
        break;
    }
    romBanks = new uint8_t*[numOfAddBanks];
    for (int i = 0; i < numOfAddBanks; ++i) {
        romBanks[i] = new uint8_t[16384];
        cartridge.read(reinterpret_cast<char*>(romBanks[i]), 16384);
    }

    write(0xFF05, 0x00);
    write(0xFF06, 0x00);
    write(0xFF07, 0x00);
    write(0xFF10, 0x80);
    write(0xFF11, 0xBF);
    write(0xFF12, 0xF3);
    write(0xFF14, 0xBF);
    write(0xFF16, 0x3F);
    write(0xFF17, 0x00);
    write(0xFF19, 0xBF);
    write(0xFF1A, 0x7F);
    write(0xFF1B, 0xFF);
    write(0xFF1C, 0x9F);
    write(0xFF1E, 0xBF);
    write(0xFF20, 0xFF);
    write(0xFF21, 0x00);
    write(0xFF22, 0x00);
    write(0xFF23, 0xBF);
    write(0xFF24, 0x77);
    write(0xFF25, 0xF3);
    write(0xFF26, 0xF1);
    write(0xFF40, 0x91);
    write(0xFF42, 0x00);
    write(0xFF43, 0x00);
    write(0xFF45, 0x00);
    write(0xFF47, 0xFC);
    write(0xFF48, 0xFF);
    write(0xFF49, 0xFF);
    write(0xFF4A, 0x00);
    write(0xFF4B, 0x00);
    write(0xFFFF, 0x00);
}

Memory::~Memory() {
    delete ieReg;
    delete[] highRam;
    delete[] ioPorts;
    delete[] spriteAttTab;
    delete[] internalRam;
    delete[] externalRam;
    delete[] videoRam;
    delete[] romBank0;
    for (int i = 0; i < numOfAddBanks; ++i) {
        delete[] romBanks[i];
    }
    delete[] romBanks;
}

uint8_t Memory::read(uint16_t address) {
    uint8_t *memLoc = resolveAddress(address);
    return *memLoc;
}

void Memory::write(uint16_t address, uint8_t value) {
    uint8_t *memLoc = resolveAddress(address);
    *memLoc = value;

    // FF46 - DMA - DMA Transfer and Start Address (W)
    if (address == 0xFF46) {
        uint16_t startAddr = read(0xFF46) * 0x100;
        for (int i = 0; i < 160; ++i) {
            write(0xFE00+i, read(startAddr+i));
        }
    }
}

uint16_t Memory::readW(uint16_t address) {
    return (read(address+1) << 8) | read(address);
}

void Memory::writeW(uint16_t address, uint16_t value) {
    write(address, value & 0x00FF);
    write(address+1, (value & 0xFF00) >> 8);
}

void Memory::dumpCartridgeToFile(const std::string &file) {
    std::ofstream cartridge(file, std::ios::binary);
    cartridge.write((const char*)romBank0, 16384);
    for (int i = 0; i < numOfAddBanks; ++i) {
        cartridge.write((const char*)romBanks[i], 16384);
    }
}

void Memory::dumpToFile(const std::string &file) {
    std::ofstream cartridge(file, std::ios::binary);
    cartridge.write((const char*)romBank0, 16384);
    for (int i = 0; i < numOfAddBanks; ++i) {
        cartridge.write((const char*)romBanks[i], 16384);
    }
    cartridge.write((const char*)videoRam, 8192);
    cartridge.write((const char*)externalRam, 8192);
    cartridge.write((const char*)internalRam, 8192);
    cartridge.write((const char*)internalRam, 7680);
    cartridge.write((const char*)spriteAttTab, 160);
    cartridge.write((const char*)ioPorts, 224);
    cartridge.write((const char*)highRam, 127);
    cartridge.write((const char*)ieReg, 1);
}

uint8_t* Memory::resolveAddress(uint16_t address) {
    if (address <= 0x3FFF) {
        return romBank0 + address;
    }
    if ((address >= 0x4000) && (address <= 0x7FFF)) {
        return romBanks[selectedAddBank] + address - 0x4000;
    }
    if ((address >= 0x8000) && (address <= 0x9FFF)) {
        return videoRam + address - 0x8000;
    }
    if ((address >= 0xA000) && (address <= 0xBFFF)) {
        return externalRam + address - 0xA000;
    }
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
