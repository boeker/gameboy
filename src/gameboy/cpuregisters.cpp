#include "cpuregisters.h"

namespace gameboy {
CPURegisters::CPURegisters() :
    interruptMasterEnable(false) {
    registers = new uint8_t[8];
    setAF(0x01B0);
    setBC(0x0013);
    setDE(0x00D8);
    setHL(0x014D);
    setSP(0xFFFE);

    pc = 0x0100;
}

CPURegisters::~CPURegisters() {
    delete[] registers;
}

void CPURegisters::setA(uint8_t value) {
    registers[0] = value;
}

void CPURegisters::setB(uint8_t value) {
    registers[1] = value;
}

void CPURegisters::setC(uint8_t value) {
    registers[2] = value;
}

void CPURegisters::setD(uint8_t value) {
    registers[3] = value;
}

void CPURegisters::setE(uint8_t value) {
    registers[4] = value;
}

void CPURegisters::setF(uint8_t value) {
    registers[5] = value;
}

void CPURegisters::setH(uint8_t value) {
    registers[6] = value;
}

void CPURegisters::setL(uint8_t value) {
    registers[7] = value;
}

uint8_t CPURegisters::getA() const {
    return registers[0];
}

uint8_t CPURegisters::getB() const {
    return registers[1];
}

uint8_t CPURegisters::getC() const {
    return registers[2];
}

uint8_t CPURegisters::getD() const {
    return registers[3];
}

uint8_t CPURegisters::getE() const {
    return registers[4];
}

uint8_t CPURegisters::getF() const {
    return registers[5];
}

uint8_t CPURegisters::getH() const {
    return registers[6];
}

uint8_t CPURegisters::getL() const {
    return registers[7];
}

void CPURegisters::setAF(uint16_t value) {
    registers[0] = (value & 0xFF00) >> 8;
    registers[5] = value & 0x00FF;
}

void CPURegisters::setBC(uint16_t value) {
    registers[1] = (value & 0xFF00) >> 8;
    registers[2] = value & 0x00FF;
}

void CPURegisters::setDE(uint16_t value) {
    registers[3] = (value & 0xFF00) >> 8;
    registers[4] = value & 0x00FF;
}

void CPURegisters::setHL(uint16_t value) {
    registers[6] = (value & 0xFF00) >> 8;
    registers[7] = value & 0x00FF;
}

uint16_t CPURegisters::getAF() const {
    return (registers[0] << 8) | registers[5];
}

uint16_t CPURegisters::getBC() const {
    return (registers[1] << 8) | registers[2];
}

uint16_t CPURegisters::getDE() const {
    return (registers[3] << 8) | registers[4];
}

uint16_t CPURegisters::getHL() const {
    return (registers[6] << 8) | registers[7];
}

void CPURegisters::setZeroFlag(bool flag) {
    setFlag(7, flag);
}

void CPURegisters::setSubFlag(bool flag) {
    setFlag(6, flag);
}

void CPURegisters::setHalfCarryFlag(bool flag) {
    setFlag(5, flag);
}

void CPURegisters::setCarryFlag(bool flag) {
    setFlag(4, flag);
}

bool CPURegisters::getZeroFlag() const {
    return getFlag(7);
}

bool CPURegisters::getSubFlag() const {
    return getFlag(6);
}

bool CPURegisters::getHalfCarryFlag() const {
    return getFlag(5);
}

bool CPURegisters::getCarryFlag() const {
    return getFlag(4);
}


void CPURegisters::setSP(uint16_t value) {
    stackPointer = value;
}

uint16_t CPURegisters::getSP() const {
    return stackPointer;
}

void CPURegisters::setIME(bool flag) {
    interruptMasterEnable = flag;
}

bool CPURegisters::getIME() {
    return interruptMasterEnable;
}

void CPURegisters::setFlag(unsigned int bitpos, bool flag) {
    if (flag) {
        registers[5] = registers[5] | (0x1 << bitpos);
    } else {
        registers[5] = registers[5] & ~(0x1 << bitpos);
    }
}

bool CPURegisters::getFlag(unsigned int bitpos) const {
    return (registers[5] & (0x1 << bitpos)) != 0;
}
}
