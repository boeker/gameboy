#include "core.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include "cpuregisters.h"
#include "keyboard.h"
#include "memory.h"
#include "screen.h"

namespace gameboy {
Core::Core(const std::string &file) :
    registers(new CPURegisters),
    memory(new Memory(file)),
    screen(new Screen(memory)),
    keyboard(new Keyboard()),
    lastClocks(0),
    clock(0) {
}

Core::~Core() {
    delete keyboard;
    delete screen;
    delete memory;
    delete registers;
}

Keyboard* Core::getKeyboard() {
    return keyboard;
}

util::Color* Core::getFramebuffer() {
    return screen->getFramebuffer();
}

bool Core::drawFlagSet() {
    return screen->drawFlagSet();
}

void Core::emulateCycle() {
    (this->*opCodes[memory->read(registers->pc++)])();
    clock += lastClocks;
    screen->step(lastClocks);
    updateKeyRegister();
}

void Core::emulateUntilVBlank() {
    do {
        emulateCycle();
    } while (!screen->drawFlagSet());
}

void Core::updateKeyRegister() { //Keys are active-low
    if ((memory->read(0xFF00) & 0x20) == 0) { //Bit 5
        if (keyboard->start) {
            memory->write(0xFF00, memory->read(0xFF00) &  0xF7);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x08);
        }
        if (keyboard->select) {
            memory->write(0xFF00, memory->read(0xFF00) &  0xFB);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x04);
        }
        if (keyboard->b) {
            memory->write(0xFF00, memory->read(0xFF00) &  0xFD);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x02);
        }
        if (keyboard->a) {
            memory->write(0xFF00, memory->read(0xFF00) &  0xFE);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x01);
        }
    } else if ((memory->read(0xFF00) & 0x10) == 0) { //Bit 4
        if (keyboard->down) {
            memory->write(0xFF00, memory->read(0xFF00) &  0xF7);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x08);
        }
        if (keyboard->up) {
            memory->write(0xFF00, memory->read(0xFF00) &  0xFB);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x04);
        }
        if (keyboard->left) {
            memory->write(0xFF00, memory->read(0xFF00) &  0xFD);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x02);
        }
        if (keyboard->right) {
            memory->write(0xFF00, memory->read(0xFF00) &  0xFE);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x01);
        }
    }
}

void Core::opcdump() {
    //log("|-----");
    //log(memory->read(registers->pc));
    //log("@");
    //log(registers->pc);
    //log(", ");
    //log(clock);
    //log("-----|\n");
    //log(": ");
    //log("\n");
}

void Core::regdump() {
    //log("AF: ");
    //log(registers->getAF());
    //log("A: ");
    //log(registers->getA());
    //log(", ");
    //log("BC: ");
    //log(registers->getBC());
    //log(", ");
    //log("DE: ");
    //log(registers->getDE());
    //log(", ");
    //log("HL: ");
    //log(registers->getHL());
    //log(", ");
    //log("SP: ");
    //log(registers->getSP());
    //log(", ");
    //log("Z: ");
    //log(registers->getZeroFlag() ? "true" : "false");
    //log(", ");
    //log("N: ");
    //log(registers->getSubFlag() ? "true" : "false");
    //log(", ");
    //log("H: ");
    //log(registers->getHalfCarryFlag() ? "true" : "false");
    //log(", ");
    //log("C: ");
    //log(registers->getCarryFlag() ? "true" : "false");
    //log("\n");
}

void Core::sysdump() {
    memory->dumpToFile("dump.bin");
}

void Core::handleCB() {
    (this->*opCodesCB[memory->read(registers->pc++)])();
}

void Core::xx() {
    /*log("Unknown opcode: ");
    log(memory->read(registers->pc-1));
    log(" at ");
    log(registers->pc-1);
    log("\n");
    exit(EXIT_FAILURE);*/
}

void Core::CBxx() {
    /*log("Unknown opcode: ");
    log("CB ");
    log(memory->read(registers->pc-1));
    log(" at ");
    log(registers->pc-2);
    log("\n");
    exit(EXIT_FAILURE);*/
}

//----------8-BIT LOADS----------//
//register = n
void Core::LDrnA() { registers->setA(memory->read(registers->pc++)); lastClocks = 2; }
void Core::LDrnB() { registers->setB(memory->read(registers->pc++)); lastClocks = 2; }
void Core::LDrnC() { registers->setC(memory->read(registers->pc++)); lastClocks = 2; }
void Core::LDrnD() { registers->setD(memory->read(registers->pc++)); lastClocks = 2; }
void Core::LDrnE() { registers->setE(memory->read(registers->pc++)); lastClocks = 2; }
void Core::LDrnH() { registers->setH(memory->read(registers->pc++)); lastClocks = 2; }
void Core::LDrnL() { registers->setL(memory->read(registers->pc++)); lastClocks = 2; }

//register = register
//A
void Core::LDrrAA() { registers->setA(registers->getA()); lastClocks = 1; }
void Core::LDrrAB() { registers->setA(registers->getB()); lastClocks = 1; }
void Core::LDrrAC() { registers->setA(registers->getC()); lastClocks = 1; }
void Core::LDrrAD() { registers->setA(registers->getD()); lastClocks = 1; }
void Core::LDrrAE() { registers->setA(registers->getE()); lastClocks = 1; }
void Core::LDrrAH() { registers->setA(registers->getH()); lastClocks = 1; }
void Core::LDrrAL() { registers->setA(registers->getL()); lastClocks = 1; }
//B
void Core::LDrrBA() { registers->setB(registers->getA()); lastClocks = 1; }
void Core::LDrrBB() { registers->setB(registers->getB()); lastClocks = 1; }
void Core::LDrrBC() { registers->setB(registers->getC()); lastClocks = 1; }
void Core::LDrrBD() { registers->setB(registers->getD()); lastClocks = 1; }
void Core::LDrrBE() { registers->setB(registers->getE()); lastClocks = 1; }
void Core::LDrrBH() { registers->setB(registers->getH()); lastClocks = 1; }
void Core::LDrrBL() { registers->setB(registers->getL()); lastClocks = 1; }
//C
void Core::LDrrCA() { registers->setC(registers->getA()); lastClocks = 1; }
void Core::LDrrCB() { registers->setC(registers->getB()); lastClocks = 1; }
void Core::LDrrCC() { registers->setC(registers->getC()); lastClocks = 1; }
void Core::LDrrCD() { registers->setC(registers->getD()); lastClocks = 1; }
void Core::LDrrCE() { registers->setC(registers->getE()); lastClocks = 1; }
void Core::LDrrCH() { registers->setC(registers->getH()); lastClocks = 1; }
void Core::LDrrCL() { registers->setC(registers->getL()); lastClocks = 1; }
//D
void Core::LDrrDA() { registers->setD(registers->getA()); lastClocks = 1; }
void Core::LDrrDB() { registers->setD(registers->getB()); lastClocks = 1; }
void Core::LDrrDC() { registers->setD(registers->getC()); lastClocks = 1; }
void Core::LDrrDD() { registers->setD(registers->getD()); lastClocks = 1; }
void Core::LDrrDE() { registers->setD(registers->getE()); lastClocks = 1; }
void Core::LDrrDH() { registers->setD(registers->getH()); lastClocks = 1; }
void Core::LDrrDL() { registers->setD(registers->getL()); lastClocks = 1; }
//E
void Core::LDrrEA() { registers->setE(registers->getA()); lastClocks = 1; }
void Core::LDrrEB() { registers->setE(registers->getB()); lastClocks = 1; }
void Core::LDrrEC() { registers->setE(registers->getC()); lastClocks = 1; }
void Core::LDrrED() { registers->setE(registers->getD()); lastClocks = 1; }
void Core::LDrrEE() { registers->setE(registers->getE()); lastClocks = 1; }
void Core::LDrrEH() { registers->setE(registers->getH()); lastClocks = 1; }
void Core::LDrrEL() { registers->setE(registers->getL()); lastClocks = 1; }
//H
void Core::LDrrHA() { registers->setH(registers->getA()); lastClocks = 1; }
void Core::LDrrHB() { registers->setH(registers->getB()); lastClocks = 1; }
void Core::LDrrHC() { registers->setH(registers->getC()); lastClocks = 1; }
void Core::LDrrHD() { registers->setH(registers->getD()); lastClocks = 1; }
void Core::LDrrHE() { registers->setH(registers->getE()); lastClocks = 1; }
void Core::LDrrHH() { registers->setH(registers->getH()); lastClocks = 1; }
void Core::LDrrHL() { registers->setH(registers->getL()); lastClocks = 1; }
//L
void Core::LDrrLA() { registers->setL(registers->getA()); lastClocks = 1; }
void Core::LDrrLB() { registers->setL(registers->getB()); lastClocks = 1; }
void Core::LDrrLC() { registers->setL(registers->getC()); lastClocks = 1; }
void Core::LDrrLD() { registers->setL(registers->getD()); lastClocks = 1; }
void Core::LDrrLE() { registers->setL(registers->getE()); lastClocks = 1; }
void Core::LDrrLH() { registers->setL(registers->getH()); lastClocks = 1; }
void Core::LDrrLL() { registers->setL(registers->getL()); lastClocks = 1; }

//register = (HL)
void Core::LDrHLMA() { registers->setA(memory->read(registers->getHL())); lastClocks = 2; }
void Core::LDrHLMB() { registers->setB(memory->read(registers->getHL())); lastClocks = 2; }
void Core::LDrHLMC() { registers->setC(memory->read(registers->getHL())); lastClocks = 2; }
void Core::LDrHLMD() { registers->setD(memory->read(registers->getHL())); lastClocks = 2; }
void Core::LDrHLME() { registers->setE(memory->read(registers->getHL())); lastClocks = 2; }
void Core::LDrHLMH() { registers->setH(memory->read(registers->getHL())); lastClocks = 2; }
void Core::LDrHLML() { registers->setL(memory->read(registers->getHL())); lastClocks = 2; }

//A = (RR)
void Core::LDABCM() { registers->setA(memory->read(registers->getBC())); lastClocks = 2; }
void Core::LDADEM() { registers->setA(memory->read(registers->getDE())); lastClocks = 2; }
void Core::LDAmm() { registers->setA(memory->read(memory->readW(registers->pc))); registers->pc += 2; lastClocks = 4; }

//(HL) = register
void Core::LDHLMrA() { memory->write(registers->getHL(), registers->getA()); lastClocks = 2; }
void Core::LDHLMrB() { memory->write(registers->getHL(), registers->getB()); lastClocks = 2; }
void Core::LDHLMrC() { memory->write(registers->getHL(), registers->getC()); lastClocks = 2; }
void Core::LDHLMrD() { memory->write(registers->getHL(), registers->getD()); lastClocks = 2; }
void Core::LDHLMrE() { memory->write(registers->getHL(), registers->getE()); lastClocks = 2; }
void Core::LDHLMrH() { memory->write(registers->getHL(), registers->getH()); lastClocks = 2; }
void Core::LDHLMrL() { memory->write(registers->getHL(), registers->getL()); lastClocks = 2; }

void Core::LDHLmn() { memory->write(registers->getHL(), memory->read(registers->pc)); ++registers->pc; lastClocks = 3; }

//(RR) = A
void Core::LDBCMA() { memory->write(registers->getBC(), registers->getA()); lastClocks = 2; }
void Core::LDDEMA() { memory->write(registers->getDE(), registers->getA()); lastClocks = 2; }
//(nn) = A
void Core::LDnnA() { uint16_t nn = memory->readW(registers->pc); memory->write(nn, registers->getA()); registers->pc += 2; lastClocks = 4; }

//(HL) = register, --HL
void Core::LDDHLA() { memory->write(registers->getHL(), registers->getA()); registers->setHL(registers->getHL()-1); lastClocks = 2; }
//register = (HL), --HL
void Core::LDDAHL() { registers->setA(memory->read(registers->getHL())); registers->setHL(registers->getHL()-1); lastClocks = 2; }
//(HL) = register, ++HL
void Core::LDIHLA() { memory->write(registers->getHL(), registers->getA()); registers->setHL(registers->getHL()+1); lastClocks = 2; }
//register = (HL), ++HL
void Core::LDIAHL() { registers->setA(memory->read(registers->getHL())); registers->setHL(registers->getHL()+1); lastClocks = 2; }

//(0xFF00+n) = A
void Core::LDIOnA() { uint8_t n = memory->read(registers->pc++); memory->write(0xFF00+n, registers->getA()); lastClocks = 3; }
//A = (0xFF00+n)
void Core::LDAIOn() { uint8_t n = memory->read(registers->pc++); registers->setA(memory->read(0xFF00+n)); lastClocks = 3; }
//(0xFF00+C) = A
void Core::LDIOCA() { memory->write(0xFF00+registers->getC(), registers->getA()); lastClocks = 2; }
//A = (0xFF00+C)
void Core::LDAIOC() { registers->setA(memory->read(0xFF00+registers->getC())); lastClocks = 2; }

//----------16-BIT LOADS----------//
void Core::LDBCnn() { registers->setBC(memory->readW(registers->pc)); registers->pc += 2; lastClocks = 3; }
void Core::LDDEnn() { registers->setDE(memory->readW(registers->pc)); registers->pc += 2; lastClocks = 3; }
void Core::LDHLnn() { registers->setHL(memory->readW(registers->pc)); registers->pc += 2; lastClocks = 3; }
void Core::LDSPnn() { registers->setSP(memory->readW(registers->pc)); registers->pc += 2; lastClocks = 3; }

//(nn) = SP
void Core::LDnnSP() { memory->writeW(memory->readW(registers->pc), registers->getSP()); registers->pc += 2; lastClocks = 5; }

//----------8-Bit ALU----------//
void Core::ADDrA() { uint8_t n = registers->getA(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADDrB() { uint8_t n = registers->getB(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADDrC() { uint8_t n = registers->getC(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADDrD() { uint8_t n = registers->getD(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADDrE() { uint8_t n = registers->getE(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADDrH() { uint8_t n = registers->getH(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADDrL() { uint8_t n = registers->getL(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADDHLM() { uint8_t n = memory->read(registers->getHL()); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 2;}
void Core::ADDn() { uint8_t n = memory->read(registers->pc); ++registers->pc; uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 2;}

void Core::ADCrA() { uint8_t n = registers->getA(); uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADCrB() { uint8_t n = registers->getB(); uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADCrC() { uint8_t n = registers->getC(); uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADCrD() { uint8_t n = registers->getD(); uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADCrE() { uint8_t n = registers->getE(); uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADCrH() { uint8_t n = registers->getH(); uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADCrL() { uint8_t n = registers->getL(); uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 1; }
void Core::ADCHLM() { uint8_t n = memory->read(registers->getHL()); uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 2; }
void Core::ADCn() { uint8_t n = memory->read(registers->pc); ++registers->pc; uint8_t a = registers->getA(); registers->setA(a + n + (registers->getCarryFlag()?1:0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); lastClocks = 2; }

void Core::SUBrA() { uint8_t n = registers->getA(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SUBrB() { uint8_t n = registers->getB(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SUBrC() { uint8_t n = registers->getC(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SUBrD() { uint8_t n = registers->getD(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SUBrE() { uint8_t n = registers->getE(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SUBrH() { uint8_t n = registers->getH(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SUBrL() { uint8_t n = registers->getL(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SUBHLM() { uint8_t n = memory->read(registers->getHL()); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 2; }
void Core::SUBn() { uint8_t n = memory->read(registers->pc); ++registers->pc; uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 2; }

void Core::SBCrA() { uint8_t n = registers->getA(); uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SBCrB() { uint8_t n = registers->getB(); uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SBCrC() { uint8_t n = registers->getC(); uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SBCrD() { uint8_t n = registers->getD(); uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SBCrE() { uint8_t n = registers->getE(); uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SBCrH() { uint8_t n = registers->getH(); uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SBCrL() { uint8_t n = registers->getL(); uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 1; }
void Core::SBCHLM() { uint8_t n = memory->read(registers->getHL()); uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 2; }
void Core::SBCn() { uint8_t n = memory->read(registers->pc); ++registers->pc; uint8_t a = registers->getA(); registers->setA(a - n - ((registers->getCarryFlag()) ? 1 : 0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); lastClocks = 2; }

void Core::ANDrA() { uint8_t n = registers->getA(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ANDrB() { uint8_t n = registers->getB(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ANDrC() { uint8_t n = registers->getC(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ANDrD() { uint8_t n = registers->getD(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ANDrE() { uint8_t n = registers->getE(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ANDrH() { uint8_t n = registers->getH(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ANDrL() { uint8_t n = registers->getL(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ANDHLM() { uint8_t n = memory->read(registers->getHL()); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 2; }
void Core::ANDn() { uint8_t n = memory->read(registers->pc); ++registers->pc; registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); lastClocks = 2; }

void Core::ORrA() { uint8_t n = registers->getA(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ORrB() { uint8_t n = registers->getB(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ORrC() { uint8_t n = registers->getC(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ORrD() { uint8_t n = registers->getD(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ORrE() { uint8_t n = registers->getE(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ORrH() { uint8_t n = registers->getH(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ORrL() { uint8_t n = registers->getL(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::ORHLM() { uint8_t n = memory->read(registers->getHL()); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::ORn() { uint8_t n = memory->read(registers->pc); ++registers->pc; registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }

void Core::XORrA() { uint8_t n = registers->getA(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::XORrB() { uint8_t n = registers->getB(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::XORrC() { uint8_t n = registers->getC(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::XORrD() { uint8_t n = registers->getD(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::XORrE() { uint8_t n = registers->getE(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::XORrH() { uint8_t n = registers->getH(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::XORrL() { uint8_t n = registers->getL(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 1; }
void Core::XORHLM() { uint8_t n = memory->read(registers->getHL()); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::XORn() { uint8_t n = memory->read(registers->pc); ++registers->pc; registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }

void Core::CPrA() { uint8_t n = registers->getA(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 1; }
void Core::CPrB() { uint8_t n = registers->getB(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 1; }
void Core::CPrC() { uint8_t n = registers->getC(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 1; }
void Core::CPrD() { uint8_t n = registers->getD(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 1; }
void Core::CPrE() { uint8_t n = registers->getE(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 1; }
void Core::CPrH() { uint8_t n = registers->getH(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 1; }
void Core::CPrL() { uint8_t n = registers->getL(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 1; }
void Core::CPHLM() { uint8_t n = memory->read(registers->getHL()); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 2; }
void Core::CPn() { uint8_t n = memory->read(registers->pc); ++registers->pc; uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); lastClocks = 2; }

void Core::INCrA() { uint8_t n = registers->getA(); registers->setA(n+1); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); lastClocks = 1; }
void Core::INCrB() { uint8_t n = registers->getB(); registers->setB(n+1); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); lastClocks = 1; }
void Core::INCrC() { uint8_t n = registers->getC(); registers->setC(n+1); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); lastClocks = 1; }
void Core::INCrD() { uint8_t n = registers->getD(); registers->setD(n+1); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); lastClocks = 1; }
void Core::INCrE() { uint8_t n = registers->getE(); registers->setE(n+1); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); lastClocks = 1; }
void Core::INCrH() { uint8_t n = registers->getH(); registers->setH(n+1); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); lastClocks = 1; }
void Core::INCrL() { uint8_t n = registers->getL(); registers->setL(n+1); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); lastClocks = 1; }
void Core::INCHLM() { uint8_t n = memory->read(registers->getHL()); memory->write(registers->getHL(), n+1); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); lastClocks = 3; }

void Core::DECrA() { uint8_t n = registers->getA(); registers->setA(n-1); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); lastClocks = 1; }
void Core::DECrB() { uint8_t n = registers->getB(); registers->setB(n-1); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); lastClocks = 1; }
void Core::DECrC() { uint8_t n = registers->getC(); registers->setC(n-1); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); lastClocks = 1; }
void Core::DECrD() { uint8_t n = registers->getD(); registers->setD(n-1); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); lastClocks = 1; }
void Core::DECrE() { uint8_t n = registers->getE(); registers->setE(n-1); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); lastClocks = 1; }
void Core::DECrH() { uint8_t n = registers->getH(); registers->setH(n-1); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); lastClocks = 1; }
void Core::DECrL() { uint8_t n = registers->getL(); registers->setL(n-1); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); lastClocks = 1; }
void Core::DECHLM() { uint8_t n = memory->read(registers->getHL()); memory->write(registers->getHL(), n-1); registers->setZeroFlag(n-1 == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); lastClocks = 3; }

//----------16-BIT ARITHMETIC----------//
void Core::INCBC() { registers->setBC(registers->getBC()+1); lastClocks = 2; }
void Core::INCDE() { registers->setDE(registers->getDE()+1); lastClocks = 2; }
void Core::INCHL() { registers->setHL(registers->getHL()+1); lastClocks = 2; }
void Core::INCSP() { registers->setSP(registers->getSP()+1); lastClocks = 2; }

void Core::DECBC() { registers->setBC(registers->getBC()-1); lastClocks = 2; }
void Core::DECDE() { registers->setDE(registers->getDE()-1); lastClocks = 2; }
void Core::DECHL() { registers->setHL(registers->getHL()-1); lastClocks = 2; }
void Core::DECSP() { registers->setSP(registers->getSP()-1); lastClocks = 2; }

void Core::ADDHLBC() { uint16_t n = registers->getBC(); uint16_t reg = registers->getHL(); registers->setHL(registers->getHL() + n); registers->setSubFlag(false); registers->setHalfCarryFlag((((reg & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((reg + n) > 0xFFFF); lastClocks = 2; }
void Core::ADDHLDE() { uint16_t n = registers->getDE(); uint16_t reg = registers->getHL(); registers->setHL(registers->getHL() + n); registers->setSubFlag(false); registers->setHalfCarryFlag((((reg & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((reg + n) > 0xFFFF); lastClocks = 2; }
void Core::ADDHLHL() { uint16_t n = registers->getHL(); uint16_t reg = registers->getHL(); registers->setHL(registers->getHL() + n); registers->setSubFlag(false); registers->setHalfCarryFlag((((reg & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((reg + n) > 0xFFFF); lastClocks = 2; }
void Core::ADDHLSP() { uint16_t n = registers->getSP(); uint16_t reg = registers->getHL(); registers->setHL(registers->getHL() + n); registers->setSubFlag(false); registers->setHalfCarryFlag((((reg & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((reg + n) > 0xFFFF); lastClocks = 2; }

//TODO Check the HCF
void Core::ADDSPn() { int8_t n = (int8_t)memory->read(registers->pc); uint16_t sp = registers->getSP(); registers->setSP(sp + n); registers->setZeroFlag(false); registers->setSubFlag(false); registers->setHalfCarryFlag((((sp & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((sp + n) > 0xFFFF); ++registers->pc; lastClocks = 4; }

//----------JUMPS----------//
void Core::JPnn() { registers->pc = memory->readW(registers->pc); lastClocks = 3; }

void Core::JPHL() { registers->pc = registers->getHL(); lastClocks = 1; }

//jump on condition
void Core::JPNZnn() { lastClocks = 3; if (!registers->getZeroFlag()) { ++lastClocks; registers->pc = memory->readW(registers->pc); } else { registers->pc += 2; } }
void Core::JPZnn() { lastClocks = 3; if (registers->getZeroFlag()) { ++lastClocks; registers->pc = memory->readW(registers->pc); } else { registers->pc += 2; } }
void Core::JPNCnn() { lastClocks = 3; if (!registers->getCarryFlag()) { ++lastClocks; registers->pc = memory->readW(registers->pc); } else { registers->pc += 2; } }
void Core::JPCnn() { lastClocks = 3; if (registers->getCarryFlag()) { ++lastClocks; registers->pc = memory->readW(registers->pc); } else { registers->pc += 2; } }

//jump to pc+n on condition
void Core::JRn() { int8_t val = (int8_t)memory->read(registers->pc); ++registers->pc; lastClocks = 2; registers->pc += val; ++lastClocks; }
void Core::JRNZn() { int8_t val = (int8_t)memory->read(registers->pc); ++registers->pc; lastClocks = 2; if (!registers->getZeroFlag()) { registers->pc += val; ++lastClocks; } }
void Core::JRZn() { int8_t val = (int8_t)memory->read(registers->pc); ++registers->pc; lastClocks = 2; if (registers->getZeroFlag()) { registers->pc += val; ++lastClocks; } }
void Core::JRNCn() { int8_t val = (int8_t)memory->read(registers->pc); ++registers->pc; lastClocks = 2; if (!registers->getCarryFlag()) { registers->pc += val; ++lastClocks; } }
void Core::JRCn() { int8_t val = (int8_t)memory->read(registers->pc); ++registers->pc; lastClocks = 2; if (registers->getCarryFlag()) { registers->pc += val; ++lastClocks; } }

//----------CALLS----------//
void Core::CALLnn() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); lastClocks = 6; }
void Core::CALLNZnn() { lastClocks = 3; if (!registers->getZeroFlag()) { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); lastClocks += 3; } else { registers->pc += 2; } }
void Core::CALLZnn() { lastClocks = 3; if (registers->getZeroFlag()) { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); lastClocks += 3; } else { registers->pc += 2; } }
void Core::CALLNCnn() { lastClocks = 3; if (!registers->getCarryFlag()) { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); lastClocks += 3; } else { registers->pc += 2; } }
void Core::CALLCnn() { lastClocks = 3; if (registers->getCarryFlag()) { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); lastClocks += 3; } else { registers->pc += 2; } }

//----------RETURNS----------//
void Core::RET() { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); lastClocks = 4; }
void Core::RETI() { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); registers->setIME(true); lastClocks = 4; }

void Core::RETNZ() { lastClocks = 2; if (!registers->getZeroFlag()) { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); lastClocks += 3; } }
void Core::RETZ() { lastClocks = 2; if (registers->getZeroFlag()) { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); lastClocks += 3; } }
void Core::RETNC() { lastClocks = 2; if (!registers->getCarryFlag()) { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); lastClocks += 3; } }
void Core::RETC() { lastClocks = 2; if (registers->getCarryFlag()) { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); lastClocks += 3; } }

//----------STACK STUFF----------//
void Core::PUSHAF() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->getAF()); lastClocks = 3; }
void Core::PUSHBC() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->getBC()); lastClocks = 3; }
void Core::PUSHDE() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->getDE()); lastClocks = 3; }
void Core::PUSHHL() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->getHL()); lastClocks = 3; }

void Core::POPAF() { registers->setAF(memory->readW(registers->getSP())); registers->setSP(registers->getSP()+2); lastClocks = 3; }
void Core::POPBC() { registers->setBC(memory->readW(registers->getSP())); registers->setSP(registers->getSP()+2); lastClocks = 3; }
void Core::POPDE() { registers->setDE(memory->readW(registers->getSP())); registers->setSP(registers->getSP()+2); lastClocks = 3; }
void Core::POPHL() { registers->setHL(memory->readW(registers->getSP())); registers->setSP(registers->getSP()+2); lastClocks = 3; }

//----------RESTARTS----------//
void Core::RST00() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x00; lastClocks = 4; }
void Core::RST08() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x08; lastClocks = 4; }
void Core::RST10() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x10; lastClocks = 4; }
void Core::RST18() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x18; lastClocks = 4; }
void Core::RST20() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x20; lastClocks = 4; }
void Core::RST28() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x28; lastClocks = 4; }
void Core::RST30() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x30; lastClocks = 4; }
void Core::RST38() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x38; lastClocks = 4; }

//----------MISC----------//
void Core::NOP() { lastClocks = 1; }

void Core::DI() { registers->setIME(false); lastClocks = 1; }
void Core::EI() { registers->setIME(true); lastClocks = 1; }

void Core::STOP() {
//TODO
}

void Core::SCF() { registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(true); lastClocks = 1; }

void Core::CPL() { registers->setA(registers->getA()^0xFF); registers->setSubFlag(true); registers->setHalfCarryFlag(true); lastClocks = 1; }

//----------ROTATES AND SHIFTS----------//
void Core::RRCA() { uint8_t lsb = registers->getA() & 0x1; registers->setA((registers->getA() >> 1) | (lsb << 7)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 1; }

//Also a CB Opcode
void Core::RLCA() { uint8_t msb = registers->getA() & 0x80; registers->setA((registers->getA() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }

//||===============================================||
//||======================OB=======================||
//||====================OPCODES====================||
//||===============================================||

void Core::SWAPrA() { uint8_t n = registers->getA(); registers->setA(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::SWAPrB() { uint8_t n = registers->getB(); registers->setB(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::SWAPrC() { uint8_t n = registers->getC(); registers->setC(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::SWAPrD() { uint8_t n = registers->getD(); registers->setD(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::SWAPrE() { uint8_t n = registers->getE(); registers->setE(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::SWAPrH() { uint8_t n = registers->getH(); registers->setH(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::SWAPrL() { uint8_t n = registers->getL(); registers->setL(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 2; }
void Core::SWAPrHLm() { uint8_t n = memory->read(registers->getHL()); memory->write(registers->getHL(), (((n & 0x0F) << 4) | ((n & 0xF0) >> 4))); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); lastClocks = 4; }

//----------ROTATES AND SHIFTS----------//
void Core::RLCB() { uint8_t msb = registers->getB() & 0x80; registers->setB((registers->getB() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLCC() { uint8_t msb = registers->getC() & 0x80; registers->setC((registers->getC() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLCD() { uint8_t msb = registers->getD() & 0x80; registers->setD((registers->getD() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLCE() { uint8_t msb = registers->getE() & 0x80; registers->setE((registers->getE() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLCH() { uint8_t msb = registers->getH() & 0x80; registers->setH((registers->getH() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLCL() { uint8_t msb = registers->getL() & 0x80; registers->setL((registers->getL() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLCHLM() { uint8_t msb = memory->read(registers->getHL()) & 0x80; memory->write(registers->getHL(), (memory->read(registers->getHL()) << 1) | (msb >> 7)); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 4; }

void Core::RLA() { uint8_t msb = registers->getA() & 0x80; registers->setA((registers->getA() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLB() { uint8_t msb = registers->getB() & 0x80; registers->setB((registers->getB() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLC() { uint8_t msb = registers->getC() & 0x80; registers->setC((registers->getC() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLD() { uint8_t msb = registers->getD() & 0x80; registers->setD((registers->getD() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLE() { uint8_t msb = registers->getE() & 0x80; registers->setE((registers->getE() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLH() { uint8_t msb = registers->getH() & 0x80; registers->setH((registers->getH() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLL() { uint8_t msb = registers->getL() & 0x80; registers->setL((registers->getL() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 2; }
void Core::RLHLM() { uint8_t msb = memory->read(registers->getHL()) & 0x80; memory->write(registers->getHL(), (memory->read(registers->getHL()) << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); lastClocks = 4; }

void Core::RRA() { uint8_t lsb = registers->getA() & 0x01; registers->setA((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getA() >> 1)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 2; }
void Core::RRB() { uint8_t lsb = registers->getB() & 0x01; registers->setB((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getB() >> 1)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 2; }
void Core::RRC() { uint8_t lsb = registers->getC() & 0x01; registers->setC((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getC() >> 1)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 2; }
void Core::RRD() { uint8_t lsb = registers->getD() & 0x01; registers->setD((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getD() >> 1)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 2; }
void Core::RRE() { uint8_t lsb = registers->getE() & 0x01; registers->setE((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getE() >> 1)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 2; }
void Core::RRH() { uint8_t lsb = registers->getH() & 0x01; registers->setH((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getH() >> 1)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 2; }
void Core::RRL() { uint8_t lsb = registers->getL() & 0x01; registers->setL((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getL() >> 1)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 2; }
void Core::RRHLM() { uint8_t lsb = memory->read(registers->getHL()) & 0x01; memory->write(registers->getHL(), (((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (memory->read(registers->getHL()) >> 1)); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); lastClocks = 2; }

const Core::opCode Core::opCodes[] = {
    //00
    &Core::NOP,        &Core::LDBCnn,    &Core::LDBCMA,    &Core::INCBC,
    &Core::INCrB,    &Core::DECrB,    &Core::LDrnB,    &Core::RLCA,
    &Core::LDnnSP,    &Core::ADDHLBC,    &Core::LDABCM,    &Core::DECBC,
    &Core::INCrC,    &Core::DECrC,    &Core::LDrnC,    &Core::RRCA,
    //10
    &Core::xx,        &Core::LDDEnn,    &Core::LDDEMA,    &Core::INCDE,
    &Core::INCrD,    &Core::DECrD,    &Core::LDrnD,    &Core::xx,
    &Core::JRn,        &Core::ADDHLDE,    &Core::LDADEM,    &Core::DECDE,
    &Core::INCrE,    &Core::DECrE,    &Core::LDrnE,    &Core::xx,
    //20
    &Core::JRNZn,    &Core::LDHLnn,    &Core::LDIHLA,    &Core::INCHL,
    &Core::INCrH,    &Core::DECrH,    &Core::LDrnH,    &Core::xx,
    &Core::JRZn,    &Core::ADDHLHL,    &Core::LDIAHL,    &Core::DECHL,
    &Core::INCrL,    &Core::DECrL,    &Core::LDrnL,    &Core::CPL,
    //30
    &Core::JRNCn,    &Core::LDSPnn,    &Core::LDDHLA,    &Core::INCSP,
    &Core::INCHLM,    &Core::DECHLM,    &Core::LDHLmn,    &Core::SCF,
    &Core::JRCn,    &Core::ADDHLSP,    &Core::LDDAHL,    &Core::DECSP,
    &Core::INCrA,    &Core::DECrA,    &Core::LDrnA,    &Core::xx,
    //40
    &Core::LDrrBB,    &Core::LDrrBC,    &Core::LDrrBD,    &Core::LDrrBE,
    &Core::LDrrBH,    &Core::LDrrBL,    &Core::LDrHLMB,    &Core::LDrrBA,
    &Core::LDrrCB,    &Core::LDrrCC,    &Core::LDrrCD,    &Core::LDrrCE,
    &Core::LDrrCH,    &Core::LDrrCL,    &Core::LDrHLMC,    &Core::LDrrCA,
    //50
    &Core::LDrrDB,    &Core::LDrrDC,    &Core::LDrrDD,    &Core::LDrrDE,
    &Core::LDrrDH,    &Core::LDrrDL,    &Core::LDrHLMD,    &Core::LDrrDA,
    &Core::LDrrEB,    &Core::LDrrEC,    &Core::LDrrED,    &Core::LDrrEE,
    &Core::LDrrEH,    &Core::LDrrEL,    &Core::LDrHLME,    &Core::LDrrEA,
    //60
    &Core::LDrrHB,    &Core::LDrrHC,    &Core::LDrrHD,    &Core::LDrrHE,
    &Core::LDrrHH,    &Core::LDrrHL,    &Core::LDrHLMH,    &Core::LDrrHA,
    &Core::LDrrLB,    &Core::LDrrLC,    &Core::LDrrLD,    &Core::LDrrLE,
    &Core::LDrrLH,    &Core::LDrrLL,    &Core::LDrHLML,    &Core::LDrrLA,
    //70
    &Core::LDHLMrB,    &Core::LDHLMrC,    &Core::LDHLMrD,    &Core::LDHLMrE,
    &Core::LDHLMrH,    &Core::LDHLMrL,    &Core::xx,        &Core::LDHLMrA,
    &Core::LDrrAB,    &Core::LDrrAC,    &Core::LDrrAD,    &Core::LDrrAE,
    &Core::LDrrAH,    &Core::LDrrAL,    &Core::LDrHLMA,    &Core::LDrrAA,
    //80
    &Core::ADDrB,    &Core::ADDrC,    &Core::ADDrD,    &Core::ADDrE,
    &Core::ADDrH,    &Core::ADDrL,    &Core::ADDHLM,    &Core::ADDrA,
    &Core::ADCrB,    &Core::ADCrC,    &Core::ADCrD,    &Core::ADCrE,
    &Core::ADCrH,    &Core::ADCrL,    &Core::ADCHLM,    &Core::ADCrA,
    //90
    &Core::SUBrB,    &Core::SUBrC,    &Core::SUBrD,    &Core::SUBrE,
    &Core::SUBrH,    &Core::SUBrL,    &Core::SUBHLM,    &Core::SUBrA,
    &Core::SBCrB,    &Core::SBCrC,    &Core::SBCrD,    &Core::SBCrE,
    &Core::SBCrH,    &Core::SBCrL,    &Core::SBCHLM,    &Core::SBCrA,
    //A0
    &Core::ANDrB,    &Core::ANDrC,    &Core::ANDrD,    &Core::ANDrE,
    &Core::ANDrH,    &Core::ANDrL,    &Core::ANDHLM,    &Core::ANDrA,
    &Core::XORrB,    &Core::XORrC,    &Core::XORrD,    &Core::XORrE,
    &Core::XORrH,    &Core::XORrL,    &Core::XORHLM,    &Core::XORrA,
    //B0
    &Core::ORrB,    &Core::ORrC,    &Core::ORrD,    &Core::ORrE,
    &Core::ORrH,    &Core::ORrL,    &Core::ORHLM,    &Core::ORrA,
    &Core::CPrB,    &Core::CPrC,    &Core::CPrD,    &Core::CPrE,
    &Core::CPrH,    &Core::CPrL,    &Core::CPHLM,    &Core::CPrA,
    //C0
    &Core::RETNZ,   &Core::POPBC,   &Core::JPNZnn,    &Core::JPnn,
    &Core::CALLNZnn,&Core::PUSHBC,  &Core::ADDn,    &Core::RST00,
    &Core::RETZ,    &Core::RET,     &Core::JPZnn,    &Core::handleCB,
    &Core::CALLZnn, &Core::CALLnn,  &Core::ADCn,    &Core::RST08,
    //D0
    &Core::RETNC,    &Core::POPDE,    &Core::JPNCnn,    &Core::xx,
    &Core::CALLNCnn,&Core::PUSHDE,    &Core::SUBn,    &Core::RST10,
    &Core::RETC,    &Core::RETI,    &Core::JPCnn,    &Core::xx,
    &Core::CALLCnn,    &Core::xx,        &Core::SBCn,    &Core::RST18,
    //E0
    &Core::LDIOnA,    &Core::POPHL,    &Core::LDIOCA,    &Core::xx,
    &Core::xx,        &Core::PUSHHL,    &Core::ANDn,    &Core::RST20,
    &Core::ADDSPn,    &Core::JPHL,    &Core::LDnnA,    &Core::xx,
    &Core::xx,        &Core::xx,        &Core::XORn,    &Core::RST28,
    //F0
    &Core::LDAIOn,    &Core::POPAF,    &Core::LDAIOC,    &Core::DI,
    &Core::xx,        &Core::PUSHAF,    &Core::ORn,        &Core::RST30,
    &Core::xx,        &Core::xx,        &Core::LDAmm,    &Core::EI,
    &Core::xx,        &Core::xx,        &Core::CPn,        &Core::RST38,
};

const Core::opCode Core::opCodesCB[] = {
    //CB00
    &Core::RLCB,    &Core::RLCC,    &Core::RLCD,    &Core::RLCE,
    &Core::RLCH,    &Core::RLCL,    &Core::RLCHLM,    &Core::RLCA,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CB10
    &Core::RLB,        &Core::RLC,        &Core::RLD,        &Core::RLE,
    &Core::RLH,        &Core::RLL,        &Core::RLHLM,    &Core::RLA,
    &Core::RRB,        &Core::RRC,        &Core::RRD,        &Core::RRE,
    &Core::RRH,        &Core::RRL,        &Core::RRHLM,    &Core::RRA,
    //CB20
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CB30
    &Core::SWAPrB,    &Core::SWAPrC,    &Core::SWAPrD,    &Core::SWAPrE,
    &Core::SWAPrH,    &Core::SWAPrL,    &Core::SWAPrHLm,&Core::SWAPrA,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CB40
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CB50
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CB60
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CB70
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CB80
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CB90
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CBA0
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CBB0
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CBC0
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CBD0
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CBE0
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    //CBF0
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,    &Core::CBxx,
};
}
