#include "core.h"

#include <QDebug>
#include "cpuregisters.h"
#include "memory.h"

namespace gameboy {
//----------8-BIT LOADS----------//
//register = n
void Core::LDrnA() { registers->setA(memory->read(registers->pc++)); }
void Core::LDrnB() { registers->setB(memory->read(registers->pc++)); }
void Core::LDrnC() { registers->setC(memory->read(registers->pc++)); }
void Core::LDrnD() { registers->setD(memory->read(registers->pc++)); }
void Core::LDrnE() { registers->setE(memory->read(registers->pc++)); }
void Core::LDrnH() { registers->setH(memory->read(registers->pc++)); }
void Core::LDrnL() { registers->setL(memory->read(registers->pc++)); }

//register = register
//A
void Core::LDrrAA() { registers->setA(registers->getA()); }
void Core::LDrrAB() { registers->setA(registers->getB()); }
void Core::LDrrAC() { registers->setA(registers->getC()); }
void Core::LDrrAD() { registers->setA(registers->getD()); }
void Core::LDrrAE() { registers->setA(registers->getE()); }
void Core::LDrrAH() { registers->setA(registers->getH()); }
void Core::LDrrAL() { registers->setA(registers->getL()); }
//B
void Core::LDrrBA() { registers->setB(registers->getA()); }
void Core::LDrrBB() { registers->setB(registers->getB()); }
void Core::LDrrBC() { registers->setB(registers->getC()); }
void Core::LDrrBD() { registers->setB(registers->getD()); }
void Core::LDrrBE() { registers->setB(registers->getE()); }
void Core::LDrrBH() { registers->setB(registers->getH()); }
void Core::LDrrBL() { registers->setB(registers->getL()); }
//C
void Core::LDrrCA() { registers->setC(registers->getA()); }
void Core::LDrrCB() { registers->setC(registers->getB()); }
void Core::LDrrCC() { registers->setC(registers->getC()); }
void Core::LDrrCD() { registers->setC(registers->getD()); }
void Core::LDrrCE() { registers->setC(registers->getE()); }
void Core::LDrrCH() { registers->setC(registers->getH()); }
void Core::LDrrCL() { registers->setC(registers->getL()); }
//D
void Core::LDrrDA() { registers->setD(registers->getA()); }
void Core::LDrrDB() { registers->setD(registers->getB()); }
void Core::LDrrDC() { registers->setD(registers->getC()); }
void Core::LDrrDD() { registers->setD(registers->getD()); }
void Core::LDrrDE() { registers->setD(registers->getE()); }
void Core::LDrrDH() { registers->setD(registers->getH()); }
void Core::LDrrDL() { registers->setD(registers->getL()); }
//E
void Core::LDrrEA() { registers->setE(registers->getA()); }
void Core::LDrrEB() { registers->setE(registers->getB()); }
void Core::LDrrEC() { registers->setE(registers->getC()); }
void Core::LDrrED() { registers->setE(registers->getD()); }
void Core::LDrrEE() { registers->setE(registers->getE()); }
void Core::LDrrEH() { registers->setE(registers->getH()); }
void Core::LDrrEL() { registers->setE(registers->getL()); }
//H
void Core::LDrrHA() { registers->setH(registers->getA()); }
void Core::LDrrHB() { registers->setH(registers->getB()); }
void Core::LDrrHC() { registers->setH(registers->getC()); }
void Core::LDrrHD() { registers->setH(registers->getD()); }
void Core::LDrrHE() { registers->setH(registers->getE()); }
void Core::LDrrHH() { registers->setH(registers->getH()); }
void Core::LDrrHL() { registers->setH(registers->getL()); }
//L
void Core::LDrrLA() { registers->setL(registers->getA()); }
void Core::LDrrLB() { registers->setL(registers->getB()); }
void Core::LDrrLC() { registers->setL(registers->getC()); }
void Core::LDrrLD() { registers->setL(registers->getD()); }
void Core::LDrrLE() { registers->setL(registers->getE()); }
void Core::LDrrLH() { registers->setL(registers->getH()); }
void Core::LDrrLL() { registers->setL(registers->getL()); }

//register = (HL)
void Core::LDrHLMA() { registers->setA(memory->read(registers->getHL())); }
void Core::LDrHLMB() { registers->setB(memory->read(registers->getHL())); }
void Core::LDrHLMC() { registers->setC(memory->read(registers->getHL())); }
void Core::LDrHLMD() { registers->setD(memory->read(registers->getHL())); }
void Core::LDrHLME() { registers->setE(memory->read(registers->getHL())); }
void Core::LDrHLMH() { registers->setH(memory->read(registers->getHL())); }
void Core::LDrHLML() { registers->setL(memory->read(registers->getHL())); }

//A = (RR)
void Core::LDABCM() { registers->setA(memory->read(registers->getBC())); }
void Core::LDADEM() { registers->setA(memory->read(registers->getDE())); }
void Core::LDAmm() { registers->setA(memory->read(memory->readW(registers->pc))); registers->pc += 2; }

//(HL) = register
void Core::LDHLMrA() { memory->write(registers->getHL(), registers->getA()); }
void Core::LDHLMrB() { memory->write(registers->getHL(), registers->getB()); }
void Core::LDHLMrC() { memory->write(registers->getHL(), registers->getC()); }
void Core::LDHLMrD() { memory->write(registers->getHL(), registers->getD()); }
void Core::LDHLMrE() { memory->write(registers->getHL(), registers->getE()); }
void Core::LDHLMrH() { memory->write(registers->getHL(), registers->getH()); }
void Core::LDHLMrL() { memory->write(registers->getHL(), registers->getL()); }

void Core::LDHLmn() { memory->write(registers->getHL(), memory->read(registers->pc)); ++registers->pc; }

//(RR) = A
void Core::LDBCMA() { memory->write(registers->getBC(), registers->getA()); }
void Core::LDDEMA() { memory->write(registers->getDE(), registers->getA()); }
//(nn) = A
void Core::LDnnA() { uint16_t nn = memory->readW(registers->pc); memory->write(nn, registers->getA()); registers->pc += 2; }

//(HL) = register, --HL
void Core::LDDHLA() { memory->write(registers->getHL(), registers->getA()); registers->setHL(registers->getHL()-1); }
//register = (HL), --HL
void Core::LDDAHL() { registers->setA(memory->read(registers->getHL())); registers->setHL(registers->getHL()-1); }
//(HL) = register, ++HL
void Core::LDIHLA() { memory->write(registers->getHL(), registers->getA()); registers->setHL(registers->getHL()+1); }
//register = (HL), ++HL
void Core::LDIAHL() { registers->setA(memory->read(registers->getHL())); registers->setHL(registers->getHL()+1); }

//(0xFF00+n) = A
void Core::LDIOnA() { uint8_t n = memory->read(registers->pc++); memory->write(0xFF00+n, registers->getA()); }
//A = (0xFF00+n)
void Core::LDAIOn() { uint8_t n = memory->read(registers->pc++); registers->setA(memory->read(0xFF00+n)); }
//(0xFF00+C) = A
void Core::LDIOCA() { memory->write(0xFF00+registers->getC(), registers->getA()); }
//A = (0xFF00+C)
void Core::LDAIOC() { registers->setA(memory->read(0xFF00+registers->getC())); }

//----------16-BIT LOADS----------//
void Core::LDBCnn() { registers->setBC(memory->readW(registers->pc)); registers->pc += 2; }
void Core::LDDEnn() { registers->setDE(memory->readW(registers->pc)); registers->pc += 2; }
void Core::LDHLnn() { registers->setHL(memory->readW(registers->pc)); registers->pc += 2; }
void Core::LDSPnn() { registers->setSP(memory->readW(registers->pc)); registers->pc += 2; }

//(nn) = SP
void Core::LDnnSP() { memory->writeW(memory->readW(registers->pc), registers->getSP()); registers->pc += 2; }

//HL = SP+n
void Core::LDHLSPn() { int8_t n = memory->read(registers->pc++); uint16_t sp = registers->getSP(); uint16_t res = sp + n; registers->setHL(res); registers->setZeroFlag(false); registers->setSubFlag(false); registers->setHalfCarryFlag(((sp ^ n ^ res) & 0x10) == 0x10); registers->setCarryFlag(((sp ^ n ^ res) & 0x100) == 0x100); }

//SP = HL
void Core::LDSPHL() { registers->setSP(registers->getHL()); }

//----------8-Bit ALU----------//
void Core::ADDrA() { uint8_t n = registers->getA(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); }
void Core::ADDrB() { uint8_t n = registers->getB(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); }
void Core::ADDrC() { uint8_t n = registers->getC(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); }
void Core::ADDrD() { uint8_t n = registers->getD(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); }
void Core::ADDrE() { uint8_t n = registers->getE(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); }
void Core::ADDrH() { uint8_t n = registers->getH(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); }
void Core::ADDrL() { uint8_t n = registers->getL(); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255); }
void Core::ADDHLM() { uint8_t n = memory->read(registers->getHL()); uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255);}
void Core::ADDn() { uint8_t n = memory->read(registers->pc); ++registers->pc; uint8_t a = registers->getA(); registers->setA(a + n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((a & 0xF) + (n & 0xF)) & 0x10) != 0); registers->setCarryFlag((a + n) > 255);}

void Core::ADCrA() { uint8_t n = registers->getA(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }
void Core::ADCrB() { uint8_t n = registers->getB(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }
void Core::ADCrC() { uint8_t n = registers->getC(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }
void Core::ADCrD() { uint8_t n = registers->getD(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }
void Core::ADCrE() { uint8_t n = registers->getE(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }
void Core::ADCrH() { uint8_t n = registers->getH(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }
void Core::ADCrL() { uint8_t n = registers->getL(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }
void Core::ADCHLM() { uint8_t n = memory->read(registers->getHL()); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }
void Core::ADCn() { uint8_t n = memory->read(registers->pc++); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() + n + carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(((registers->getA() & 0x0F) + (n & 0x0F) + carry) > 0x0F); registers->setCarryFlag(res > 0xFF); registers->setA(res); }

void Core::SUBrA() { uint8_t n = registers->getA(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }
void Core::SUBrB() { uint8_t n = registers->getB(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }
void Core::SUBrC() { uint8_t n = registers->getC(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }
void Core::SUBrD() { uint8_t n = registers->getD(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }
void Core::SUBrE() { uint8_t n = registers->getE(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }
void Core::SUBrH() { uint8_t n = registers->getH(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }
void Core::SUBrL() { uint8_t n = registers->getL(); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }
void Core::SUBHLM() { uint8_t n = memory->read(registers->getHL()); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }
void Core::SUBn() { uint8_t n = memory->read(registers->pc++); uint8_t a = registers->getA(); registers->setA(a - n); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag((registers->getA()^n^a) & 0x10); registers->setCarryFlag((a - n) < 0); }

void Core::SBCrA() { uint8_t n = registers->getA(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }
void Core::SBCrB() { uint8_t n = registers->getB(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }
void Core::SBCrC() { uint8_t n = registers->getC(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }
void Core::SBCrD() { uint8_t n = registers->getD(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }
void Core::SBCrE() { uint8_t n = registers->getE(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }
void Core::SBCrH() { uint8_t n = registers->getH(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }
void Core::SBCrL() { uint8_t n = registers->getL(); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }
void Core::SBCHLM() { uint8_t n = memory->read(registers->getHL()); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }
void Core::SBCn() { uint8_t n = memory->read(registers->pc++); int carry = registers->getCarryFlag() ? 1 : 0; int res = registers->getA() - n - carry; registers->setZeroFlag(((uint8_t)res) == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((registers->getA() & 0x0F) - (n & 0x0F) - carry) < 0x0); registers->setCarryFlag(res < 0x0); registers->setA(res); }

void Core::ANDrA() { uint8_t n = registers->getA(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }
void Core::ANDrB() { uint8_t n = registers->getB(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }
void Core::ANDrC() { uint8_t n = registers->getC(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }
void Core::ANDrD() { uint8_t n = registers->getD(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }
void Core::ANDrE() { uint8_t n = registers->getE(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }
void Core::ANDrH() { uint8_t n = registers->getH(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }
void Core::ANDrL() { uint8_t n = registers->getL(); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }
void Core::ANDHLM() { uint8_t n = memory->read(registers->getHL()); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }
void Core::ANDn() { uint8_t n = memory->read(registers->pc++); registers->setA(n & registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); registers->setCarryFlag(false); }

void Core::ORrA() { uint8_t n = registers->getA(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::ORrB() { uint8_t n = registers->getB(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::ORrC() { uint8_t n = registers->getC(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::ORrD() { uint8_t n = registers->getD(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::ORrE() { uint8_t n = registers->getE(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::ORrH() { uint8_t n = registers->getH(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::ORrL() { uint8_t n = registers->getL(); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::ORHLM() { uint8_t n = memory->read(registers->getHL()); registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::ORn() { uint8_t n = memory->read(registers->pc); ++registers->pc; registers->setA(n | registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }

void Core::XORrA() { uint8_t n = registers->getA(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::XORrB() { uint8_t n = registers->getB(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::XORrC() { uint8_t n = registers->getC(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::XORrD() { uint8_t n = registers->getD(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::XORrE() { uint8_t n = registers->getE(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::XORrH() { uint8_t n = registers->getH(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::XORrL() { uint8_t n = registers->getL(); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::XORHLM() { uint8_t n = memory->read(registers->getHL()); registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::XORn() { uint8_t n = memory->read(registers->pc); ++registers->pc; registers->setA(n ^ registers->getA()); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }

void Core::CPrA() { uint8_t n = registers->getA(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }
void Core::CPrB() { uint8_t n = registers->getB(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }
void Core::CPrC() { uint8_t n = registers->getC(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }
void Core::CPrD() { uint8_t n = registers->getD(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }
void Core::CPrE() { uint8_t n = registers->getE(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }
void Core::CPrH() { uint8_t n = registers->getH(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }
void Core::CPrL() { uint8_t n = registers->getL(); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }
void Core::CPHLM() { uint8_t n = memory->read(registers->getHL()); uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }
void Core::CPn() { uint8_t n = memory->read(registers->pc); ++registers->pc; uint8_t res = registers->getA() - n; registers->setZeroFlag(registers->getA() == n); registers->setSubFlag(true); registers->setHalfCarryFlag((res^n^registers->getA()) & 0x10); registers->setCarryFlag(registers->getA() < n); }

void Core::INCrA() { uint8_t n = registers->getA(); registers->setA(n+1); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); }
void Core::INCrB() { uint8_t n = registers->getB(); registers->setB(n+1); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); }
void Core::INCrC() { uint8_t n = registers->getC(); registers->setC(n+1); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); }
void Core::INCrD() { uint8_t n = registers->getD(); registers->setD(n+1); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); }
void Core::INCrE() { uint8_t n = registers->getE(); registers->setE(n+1); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); }
void Core::INCrH() { uint8_t n = registers->getH(); registers->setH(n+1); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); }
void Core::INCrL() { uint8_t n = registers->getL(); registers->setL(n+1); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); }
void Core::INCHLM() { uint8_t n = memory->read(registers->getHL()); memory->write(registers->getHL(), n+1); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag((((n & 0xF) + 1) & 0x10) != 0); }

void Core::DECrA() { uint8_t n = registers->getA(); registers->setA(n-1); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); }
void Core::DECrB() { uint8_t n = registers->getB(); registers->setB(n-1); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); }
void Core::DECrC() { uint8_t n = registers->getC(); registers->setC(n-1); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); }
void Core::DECrD() { uint8_t n = registers->getD(); registers->setD(n-1); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); }
void Core::DECrE() { uint8_t n = registers->getE(); registers->setE(n-1); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); }
void Core::DECrH() { uint8_t n = registers->getH(); registers->setH(n-1); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); }
void Core::DECrL() { uint8_t n = registers->getL(); registers->setL(n-1); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); }
void Core::DECHLM() { uint8_t n = memory->read(registers->getHL()); memory->write(registers->getHL(), n-1); registers->setZeroFlag(n-1 == 0); registers->setSubFlag(true); registers->setHalfCarryFlag(((n-1)^1^n) & 0x10); }

//----------16-BIT ARITHMETIC----------//
void Core::INCBC() { registers->setBC(registers->getBC()+1); }
void Core::INCDE() { registers->setDE(registers->getDE()+1); }
void Core::INCHL() { registers->setHL(registers->getHL()+1); }
void Core::INCSP() { registers->setSP(registers->getSP()+1); }

void Core::DECBC() { registers->setBC(registers->getBC()-1); }
void Core::DECDE() { registers->setDE(registers->getDE()-1); }
void Core::DECHL() { registers->setHL(registers->getHL()-1); }
void Core::DECSP() { registers->setSP(registers->getSP()-1); }

void Core::ADDHLBC() { uint16_t n = registers->getBC(); uint16_t reg = registers->getHL(); registers->setHL(registers->getHL() + n); registers->setSubFlag(false); registers->setHalfCarryFlag((((reg & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((reg + n) > 0xFFFF); }
void Core::ADDHLDE() { uint16_t n = registers->getDE(); uint16_t reg = registers->getHL(); registers->setHL(registers->getHL() + n); registers->setSubFlag(false); registers->setHalfCarryFlag((((reg & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((reg + n) > 0xFFFF); }
void Core::ADDHLHL() { uint16_t n = registers->getHL(); uint16_t reg = registers->getHL(); registers->setHL(registers->getHL() + n); registers->setSubFlag(false); registers->setHalfCarryFlag((((reg & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((reg + n) > 0xFFFF); }
void Core::ADDHLSP() { uint16_t n = registers->getSP(); uint16_t reg = registers->getHL(); registers->setHL(registers->getHL() + n); registers->setSubFlag(false); registers->setHalfCarryFlag((((reg & 0xFFF) + (n & 0xFFF)) & 0x1000) != 0); registers->setCarryFlag((reg + n) > 0xFFFF); }

void Core::ADDSPn() { int8_t n = (int8_t)memory->read(registers->pc); uint16_t sp = registers->getSP(); int res = sp + n; registers->setSP(res); registers->setZeroFlag(false); registers->setSubFlag(false); registers->setHalfCarryFlag(((sp ^ n ^ (res & 0xFFFF)) & 0x10) == 0x10); registers->setCarryFlag(((sp ^ n ^ (res & 0xFFFF)) & 0x100) == 0x100); ++registers->pc; }

//----------JUMPS----------//
void Core::JPnn() { registers->pc = memory->readW(registers->pc); }

void Core::JPHL() { registers->pc = registers->getHL(); }

//jump on condition
void Core::JPNZnn() { if (!registers->getZeroFlag()) { conditional = true; registers->pc = memory->readW(registers->pc); } else { registers->pc += 2; } }
void Core::JPZnn() { if (registers->getZeroFlag()) { conditional = true; registers->pc = memory->readW(registers->pc); } else { registers->pc += 2; } }
void Core::JPNCnn() { if (!registers->getCarryFlag()) { conditional = true; registers->pc = memory->readW(registers->pc); } else { registers->pc += 2; } }
void Core::JPCnn() { if (registers->getCarryFlag()) { conditional = true; registers->pc = memory->readW(registers->pc); } else { registers->pc += 2; } }

//jump to pc+n on condition
void Core::JRn() { int8_t val = (int8_t)memory->read(registers->pc++); registers->pc += val; }
void Core::JRNZn() { int8_t val = (int8_t)memory->read(registers->pc++); if (!registers->getZeroFlag()) { registers->pc += val; conditional = true; } }
void Core::JRZn() { int8_t val = (int8_t)memory->read(registers->pc++); if (registers->getZeroFlag()) { registers->pc += val; conditional = true; } }
void Core::JRNCn() { int8_t val = (int8_t)memory->read(registers->pc++); if (!registers->getCarryFlag()) { registers->pc += val; conditional = true; } }
void Core::JRCn() { int8_t val = (int8_t)memory->read(registers->pc++); if (registers->getCarryFlag()) { registers->pc += val; conditional = true; } }

//----------CALLS----------//
void Core::CALLnn() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); }
void Core::CALLNZnn() { if (!registers->getZeroFlag()) { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); conditional = true; } else { registers->pc += 2; } }
void Core::CALLZnn() { if (registers->getZeroFlag()) { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); conditional = true; } else { registers->pc += 2; } }
void Core::CALLNCnn() { if (!registers->getCarryFlag()) { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); conditional = true; } else { registers->pc += 2; } }
void Core::CALLCnn() { if (registers->getCarryFlag()) { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc+2); registers->pc = memory->readW(registers->pc); conditional = true; } else { registers->pc += 2; } }

//----------RETURNS----------//
void Core::RET() { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); }
void Core::RETI() { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); registers->setIME(true); }

void Core::RETNZ() { if (!registers->getZeroFlag()) { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); conditional = true; } }
void Core::RETZ() { if (registers->getZeroFlag()) { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); conditional = true; } }
void Core::RETNC() { if (!registers->getCarryFlag()) { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); conditional = true; } }
void Core::RETC() { if (registers->getCarryFlag()) { registers->pc = memory->readW(registers->getSP()); registers->setSP(registers->getSP()+2); conditional = true; } }

//----------STACK STUFF----------//
void Core::PUSHAF() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->getAF()); }
void Core::PUSHBC() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->getBC()); }
void Core::PUSHDE() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->getDE()); }
void Core::PUSHHL() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->getHL()); }

//POPAF is special, retains the lower 4 Bits of F
void Core::POPAF() { registers->setAF((memory->readW(registers->getSP()) & 0xFFF0) | (registers->getAF() & 0x000F)); registers->setSP(registers->getSP()+2); }
void Core::POPBC() { registers->setBC(memory->readW(registers->getSP())); registers->setSP(registers->getSP()+2); }
void Core::POPDE() { registers->setDE(memory->readW(registers->getSP())); registers->setSP(registers->getSP()+2); }
void Core::POPHL() { registers->setHL(memory->readW(registers->getSP())); registers->setSP(registers->getSP()+2); }

//----------RESTARTS----------//
void Core::RST00() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0000; }
void Core::RST08() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0008; }
void Core::RST10() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0010; }
void Core::RST18() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0018; }
void Core::RST20() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0020; }
void Core::RST28() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0028; }
void Core::RST30() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0030; }
void Core::RST38() { registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0038; }

//---------INTERRUPTS---------//
void Core::INT40() { registers->setIME(false); registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0040; }
void Core::INT48() { registers->setIME(false); registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0048; }
void Core::INT50() { registers->setIME(false); registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0050; }
void Core::INT58() { registers->setIME(false); registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0058; }
void Core::INT60() { registers->setIME(false); registers->setSP(registers->getSP()-2); memory->writeW(registers->getSP(), registers->pc); registers->pc = 0x0060; }

//----------MISC----------//
void Core::NOP() { }

void Core::DI() { registers->setIME(false); }
void Core::EI() { registers->setIME(true); }

void Core::HALT() { uint8_t interrupt = memory->read(0xFF0F) & memory->read(0xFFFF) & 0x1F; if (!interrupt) { --registers->pc; } }

void Core::STOP() {
    // TODO
    ++registers->pc;
}

void Core::SCF() { registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(true); }

void Core::CCF() { registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(!registers->getCarryFlag()); }

void Core::CPL() { registers->setA(registers->getA()^0xFF); registers->setSubFlag(true); registers->setHalfCarryFlag(true); }

void Core::DAA() {
    int a = registers->getA();

    if (!registers->getSubFlag()) {
        if (registers->getHalfCarryFlag() || (a & 0xF) > 9) {
            a += 0x06;
        }
        if (registers->getCarryFlag() || (a > 0x9F)) {
            a += 0x60;
        }
    } else {
        if (registers->getHalfCarryFlag()) {
            a = (a - 6) & 0xFF;
        }
        if (registers->getCarryFlag()) {
            a -= 0x60;
        }
    }

    registers->setHalfCarryFlag(false);
    if ((a & 0x100) == 0x100) {
        registers->setCarryFlag(true);
    }

    a &= 0xFF;

    registers->setZeroFlag(a == 0);

    registers->setA(a);

   
}

//----------ROTATES AND SHIFTS----------//
void Core::RRCANCB() { uint8_t lsb = registers->getA() & 0x1; registers->setA((registers->getA() >> 1) | (lsb << 7)); registers->setZeroFlag(false); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }

void Core::RRANCB() { uint8_t lsb = registers->getA() & 0x01; registers->setA((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getA() >> 1)); registers->setZeroFlag(false); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }

void Core::RLCANCB() { uint8_t msb = registers->getA() & 0x80; registers->setA((registers->getA() << 1) | (msb >> 7)); registers->setZeroFlag(false); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }

void Core::RLANCB() { uint8_t carry = registers->getCarryFlag() ? 0x01 : 0x00; uint8_t msb = registers->getA() & 0x80; registers->setA((registers->getA() << 1) | carry); registers->setZeroFlag(false); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }

// ||===============================================||
// ||======================CB=======================||
// ||====================OPCODES====================||
// ||===============================================||

void Core::SWAPrA() { uint8_t n = registers->getA(); registers->setA(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::SWAPrB() { uint8_t n = registers->getB(); registers->setB(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::SWAPrC() { uint8_t n = registers->getC(); registers->setC(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::SWAPrD() { uint8_t n = registers->getD(); registers->setD(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::SWAPrE() { uint8_t n = registers->getE(); registers->setE(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::SWAPrH() { uint8_t n = registers->getH(); registers->setH(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::SWAPrL() { uint8_t n = registers->getL(); registers->setL(((n & 0x0F) << 4) | ((n & 0xF0) >> 4)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }
void Core::SWAPrHLm() { uint8_t n = memory->read(registers->getHL()); memory->write(registers->getHL(), (((n & 0x0F) << 4) | ((n & 0xF0) >> 4))); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(false); }

//----------ROTATES AND SHIFTS----------//
void Core::RLCA() { uint8_t msb = registers->getA() & 0x80; registers->setA((registers->getA() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLCB() { uint8_t msb = registers->getB() & 0x80; registers->setB((registers->getB() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLCC() { uint8_t msb = registers->getC() & 0x80; registers->setC((registers->getC() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLCD() { uint8_t msb = registers->getD() & 0x80; registers->setD((registers->getD() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLCE() { uint8_t msb = registers->getE() & 0x80; registers->setE((registers->getE() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLCH() { uint8_t msb = registers->getH() & 0x80; registers->setH((registers->getH() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLCL() { uint8_t msb = registers->getL() & 0x80; registers->setL((registers->getL() << 1) | (msb >> 7)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLCHLM() { uint8_t msb = memory->read(registers->getHL()) & 0x80; memory->write(registers->getHL(), (memory->read(registers->getHL()) << 1) | (msb >> 7)); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }

void Core::RRCA() { uint8_t lsb = registers->getA() & 0x1; registers->setA((registers->getA() >> 1) | (lsb << 7)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRCB() { uint8_t lsb = registers->getB() & 0x1; registers->setB((registers->getB() >> 1) | (lsb << 7)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRCC() { uint8_t lsb = registers->getC() & 0x1; registers->setC((registers->getC() >> 1) | (lsb << 7)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRCD() { uint8_t lsb = registers->getD() & 0x1; registers->setD((registers->getD() >> 1) | (lsb << 7)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRCE() { uint8_t lsb = registers->getE() & 0x1; registers->setE((registers->getE() >> 1) | (lsb << 7)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRCH() { uint8_t lsb = registers->getH() & 0x1; registers->setH((registers->getH() >> 1) | (lsb << 7)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRCL() { uint8_t lsb = registers->getL() & 0x1; registers->setL((registers->getL() >> 1) | (lsb << 7)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRCHL() { uint8_t lsb = memory->read(registers->getHL()) & 0x1; memory->write(registers->getHL(), (memory->read(registers->getHL()) >> 1) | (lsb << 7)); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }

void Core::RLA() { uint8_t msb = registers->getA() & 0x80; registers->setA((registers->getA() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLB() { uint8_t msb = registers->getB() & 0x80; registers->setB((registers->getB() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLC() { uint8_t msb = registers->getC() & 0x80; registers->setC((registers->getC() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLD() { uint8_t msb = registers->getD() & 0x80; registers->setD((registers->getD() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLE() { uint8_t msb = registers->getE() & 0x80; registers->setE((registers->getE() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLH() { uint8_t msb = registers->getH() & 0x80; registers->setH((registers->getH() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLL() { uint8_t msb = registers->getL() & 0x80; registers->setL((registers->getL() << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }
void Core::RLHLM() { uint8_t msb = memory->read(registers->getHL()) & 0x80; memory->write(registers->getHL(), (memory->read(registers->getHL()) << 1) | ((registers->getCarryFlag()) ? 0x1 : 0x0)); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(msb); }

void Core::RRA() { uint8_t lsb = registers->getA() & 0x01; registers->setA((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getA() >> 1)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRB() { uint8_t lsb = registers->getB() & 0x01; registers->setB((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getB() >> 1)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRC() { uint8_t lsb = registers->getC() & 0x01; registers->setC((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getC() >> 1)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRD() { uint8_t lsb = registers->getD() & 0x01; registers->setD((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getD() >> 1)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRE() { uint8_t lsb = registers->getE() & 0x01; registers->setE((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getE() >> 1)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRH() { uint8_t lsb = registers->getH() & 0x01; registers->setH((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getH() >> 1)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRL() { uint8_t lsb = registers->getL() & 0x01; registers->setL((((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (registers->getL() >> 1)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }
void Core::RRHLM() { uint8_t lsb = memory->read(registers->getHL()) & 0x01; memory->write(registers->getHL(), (((registers->getCarryFlag()) ? 0x1 : 0x0) << 7) | (memory->read(registers->getHL()) >> 1)); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); registers->setCarryFlag(lsb); }

void Core::SRLA() { registers->setCarryFlag(registers->getA() & 0x1); registers->setA(registers->getA() >> 1); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRLB() { registers->setCarryFlag(registers->getB() & 0x1); registers->setB(registers->getB() >> 1); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRLC() { registers->setCarryFlag(registers->getC() & 0x1); registers->setC(registers->getC() >> 1); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRLD() { registers->setCarryFlag(registers->getD() & 0x1); registers->setD(registers->getD() >> 1); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRLE() { registers->setCarryFlag(registers->getE() & 0x1); registers->setE(registers->getE() >> 1); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRLH() { registers->setCarryFlag(registers->getH() & 0x1); registers->setH(registers->getH() >> 1); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRLL() { registers->setCarryFlag(registers->getL() & 0x1); registers->setL(registers->getL() >> 1); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRLHL() { registers->setCarryFlag(memory->read(registers->getHL()) & 0x1); memory->write(registers->getHL(), memory->read(registers->getHL()) >> 1); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }

void Core::SLAA() { registers->setCarryFlag(registers->getA() & 0x80); registers->setA(registers->getA() << 1); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SLAB() { registers->setCarryFlag(registers->getB() & 0x80); registers->setB(registers->getB() << 1); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SLAC() { registers->setCarryFlag(registers->getC() & 0x80); registers->setC(registers->getC() << 1); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SLAD() { registers->setCarryFlag(registers->getD() & 0x80); registers->setD(registers->getD() << 1); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SLAE() { registers->setCarryFlag(registers->getE() & 0x80); registers->setE(registers->getE() << 1); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SLAH() { registers->setCarryFlag(registers->getH() & 0x80); registers->setH(registers->getH() << 1); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SLAL() { registers->setCarryFlag(registers->getL() & 0x80); registers->setL(registers->getL() << 1); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SLAHL() { registers->setCarryFlag(memory->read(registers->getHL()) & 0x80); memory->write(registers->getHL(), memory->read(registers->getHL()) << 1); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }

void Core::SRAA() { registers->setCarryFlag(registers->getA() & 0x01); registers->setA((registers->getA() & 0x80) | (registers->getA() >> 1)); registers->setZeroFlag(registers->getA() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRAB() { registers->setCarryFlag(registers->getB() & 0x01); registers->setB((registers->getB() & 0x80) | (registers->getB() >> 1)); registers->setZeroFlag(registers->getB() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRAC() { registers->setCarryFlag(registers->getC() & 0x01); registers->setC((registers->getC() & 0x80) | (registers->getC() >> 1)); registers->setZeroFlag(registers->getC() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRAD() { registers->setCarryFlag(registers->getD() & 0x01); registers->setD((registers->getD() & 0x80) | (registers->getD() >> 1)); registers->setZeroFlag(registers->getD() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRAE() { registers->setCarryFlag(registers->getE() & 0x01); registers->setE((registers->getE() & 0x80) | (registers->getE() >> 1)); registers->setZeroFlag(registers->getE() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRAH() { registers->setCarryFlag(registers->getH() & 0x01); registers->setH((registers->getH() & 0x80) | (registers->getH() >> 1)); registers->setZeroFlag(registers->getH() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRAL() { registers->setCarryFlag(registers->getL() & 0x01); registers->setL((registers->getL() & 0x80) | (registers->getL() >> 1)); registers->setZeroFlag(registers->getL() == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }
void Core::SRAHL() { registers->setCarryFlag(memory->read(registers->getHL()) & 0x01); memory->write(registers->getHL(), (memory->read(registers->getHL()) & 0x80) | (memory->read(registers->getHL()) >> 1)); registers->setZeroFlag(memory->read(registers->getHL()) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(false); }

void Core::BIT0A() { registers->setZeroFlag((registers->getA() & 0x01) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT0B() { registers->setZeroFlag((registers->getB() & 0x01) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT0C() { registers->setZeroFlag((registers->getC() & 0x01) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT0D() { registers->setZeroFlag((registers->getD() & 0x01) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT0E() { registers->setZeroFlag((registers->getE() & 0x01) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT0H() { registers->setZeroFlag((registers->getH() & 0x01) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT0L() { registers->setZeroFlag((registers->getL() & 0x01) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT0HL() { registers->setZeroFlag((memory->read(registers->getHL()) & 0x01) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }

void Core::BIT1A() { registers->setZeroFlag((registers->getA() & 0x02) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT1B() { registers->setZeroFlag((registers->getB() & 0x02) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT1C() { registers->setZeroFlag((registers->getC() & 0x02) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT1D() { registers->setZeroFlag((registers->getD() & 0x02) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT1E() { registers->setZeroFlag((registers->getE() & 0x02) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT1H() { registers->setZeroFlag((registers->getH() & 0x02) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT1L() { registers->setZeroFlag((registers->getL() & 0x02) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT1HL() { registers->setZeroFlag((memory->read(registers->getHL()) & 0x02) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }

void Core::BIT2A() { registers->setZeroFlag((registers->getA() & 0x04) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT2B() { registers->setZeroFlag((registers->getB() & 0x04) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT2C() { registers->setZeroFlag((registers->getC() & 0x04) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT2D() { registers->setZeroFlag((registers->getD() & 0x04) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT2E() { registers->setZeroFlag((registers->getE() & 0x04) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT2H() { registers->setZeroFlag((registers->getH() & 0x04) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT2L() { registers->setZeroFlag((registers->getL() & 0x04) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT2HL() { registers->setZeroFlag((memory->read(registers->getHL()) & 0x04) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }

void Core::BIT3A() { registers->setZeroFlag((registers->getA() & 0x08) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT3B() { registers->setZeroFlag((registers->getB() & 0x08) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT3C() { registers->setZeroFlag((registers->getC() & 0x08) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT3D() { registers->setZeroFlag((registers->getD() & 0x08) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT3E() { registers->setZeroFlag((registers->getE() & 0x08) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT3H() { registers->setZeroFlag((registers->getH() & 0x08) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT3L() { registers->setZeroFlag((registers->getL() & 0x08) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT3HL() { registers->setZeroFlag((memory->read(registers->getHL()) & 0x08) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }

void Core::BIT4A() { registers->setZeroFlag((registers->getA() & 0x10) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT4B() { registers->setZeroFlag((registers->getB() & 0x10) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT4C() { registers->setZeroFlag((registers->getC() & 0x10) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT4D() { registers->setZeroFlag((registers->getD() & 0x10) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT4E() { registers->setZeroFlag((registers->getE() & 0x10) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT4H() { registers->setZeroFlag((registers->getH() & 0x10) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT4L() { registers->setZeroFlag((registers->getL() & 0x10) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT4HL() { registers->setZeroFlag((memory->read(registers->getHL()) & 0x10) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }

void Core::BIT5A() { registers->setZeroFlag((registers->getA() & 0x20) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT5B() { registers->setZeroFlag((registers->getB() & 0x20) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT5C() { registers->setZeroFlag((registers->getC() & 0x20) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT5D() { registers->setZeroFlag((registers->getD() & 0x20) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT5E() { registers->setZeroFlag((registers->getE() & 0x20) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT5H() { registers->setZeroFlag((registers->getH() & 0x20) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT5L() { registers->setZeroFlag((registers->getL() & 0x20) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT5HL() { registers->setZeroFlag((memory->read(registers->getHL()) & 0x20) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }

void Core::BIT6A() { registers->setZeroFlag((registers->getA() & 0x40) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT6B() { registers->setZeroFlag((registers->getB() & 0x40) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT6C() { registers->setZeroFlag((registers->getC() & 0x40) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT6D() { registers->setZeroFlag((registers->getD() & 0x40) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT6E() { registers->setZeroFlag((registers->getE() & 0x40) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT6H() { registers->setZeroFlag((registers->getH() & 0x40) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT6L() { registers->setZeroFlag((registers->getL() & 0x40) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT6HL() { registers->setZeroFlag((memory->read(registers->getHL()) & 0x40) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }

void Core::BIT7A() { registers->setZeroFlag((registers->getA() & 0x80) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT7B() { registers->setZeroFlag((registers->getB() & 0x80) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT7C() { registers->setZeroFlag((registers->getC() & 0x80) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT7D() { registers->setZeroFlag((registers->getD() & 0x80) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT7E() { registers->setZeroFlag((registers->getE() & 0x80) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT7H() { registers->setZeroFlag((registers->getH() & 0x80) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT7L() { registers->setZeroFlag((registers->getL() & 0x80) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }
void Core::BIT7HL() { registers->setZeroFlag((memory->read(registers->getHL()) & 0x80) == 0); registers->setSubFlag(false); registers->setHalfCarryFlag(true); }

void Core::RES0A() { registers->setA(registers->getA() & 0xFE); }
void Core::RES0B() { registers->setB(registers->getB() & 0xFE); }
void Core::RES0C() { registers->setC(registers->getC() & 0xFE); }
void Core::RES0D() { registers->setD(registers->getD() & 0xFE); }
void Core::RES0E() { registers->setE(registers->getE() & 0xFE); }
void Core::RES0H() { registers->setH(registers->getH() & 0xFE); }
void Core::RES0L() { registers->setL(registers->getL() & 0xFE); }
void Core::RES0HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) & 0xFE); }

void Core::RES1A() { registers->setA(registers->getA() & 0xFD); }
void Core::RES1B() { registers->setB(registers->getB() & 0xFD); }
void Core::RES1C() { registers->setC(registers->getC() & 0xFD); }
void Core::RES1D() { registers->setD(registers->getD() & 0xFD); }
void Core::RES1E() { registers->setE(registers->getE() & 0xFD); }
void Core::RES1H() { registers->setH(registers->getH() & 0xFD); }
void Core::RES1L() { registers->setL(registers->getL() & 0xFD); }
void Core::RES1HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) & 0xFD); }

void Core::RES2A() { registers->setA(registers->getA() & 0xFB); }
void Core::RES2B() { registers->setB(registers->getB() & 0xFB); }
void Core::RES2C() { registers->setC(registers->getC() & 0xFB); }
void Core::RES2D() { registers->setD(registers->getD() & 0xFB); }
void Core::RES2E() { registers->setE(registers->getE() & 0xFB); }
void Core::RES2H() { registers->setH(registers->getH() & 0xFB); }
void Core::RES2L() { registers->setL(registers->getL() & 0xFB); }
void Core::RES2HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) & 0xFB); }

void Core::RES3A() { registers->setA(registers->getA() & 0xF7); }
void Core::RES3B() { registers->setB(registers->getB() & 0xF7); }
void Core::RES3C() { registers->setC(registers->getC() & 0xF7); }
void Core::RES3D() { registers->setD(registers->getD() & 0xF7); }
void Core::RES3E() { registers->setE(registers->getE() & 0xF7); }
void Core::RES3H() { registers->setH(registers->getH() & 0xF7); }
void Core::RES3L() { registers->setL(registers->getL() & 0xF7); }
void Core::RES3HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) & 0xF7); }

void Core::RES4A() { registers->setA(registers->getA() & 0xEF); }
void Core::RES4B() { registers->setB(registers->getB() & 0xEF); }
void Core::RES4C() { registers->setC(registers->getC() & 0xEF); }
void Core::RES4D() { registers->setD(registers->getD() & 0xEF); }
void Core::RES4E() { registers->setE(registers->getE() & 0xEF); }
void Core::RES4H() { registers->setH(registers->getH() & 0xEF); }
void Core::RES4L() { registers->setL(registers->getL() & 0xEF); }
void Core::RES4HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) & 0xEF); }

void Core::RES5A() { registers->setA(registers->getA() & 0xDF); }
void Core::RES5B() { registers->setB(registers->getB() & 0xDF); }
void Core::RES5C() { registers->setC(registers->getC() & 0xDF); }
void Core::RES5D() { registers->setD(registers->getD() & 0xDF); }
void Core::RES5E() { registers->setE(registers->getE() & 0xDF); }
void Core::RES5H() { registers->setH(registers->getH() & 0xDF); }
void Core::RES5L() { registers->setL(registers->getL() & 0xDF); }
void Core::RES5HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) & 0xDF); }

void Core::RES6A() { registers->setA(registers->getA() & 0xBF); }
void Core::RES6B() { registers->setB(registers->getB() & 0xBF); }
void Core::RES6C() { registers->setC(registers->getC() & 0xBF); }
void Core::RES6D() { registers->setD(registers->getD() & 0xBF); }
void Core::RES6E() { registers->setE(registers->getE() & 0xBF); }
void Core::RES6H() { registers->setH(registers->getH() & 0xBF); }
void Core::RES6L() { registers->setL(registers->getL() & 0xBF); }
void Core::RES6HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) & 0xBF); }

void Core::RES7A() { registers->setA(registers->getA() & 0x7F); }
void Core::RES7B() { registers->setB(registers->getB() & 0x7F); }
void Core::RES7C() { registers->setC(registers->getC() & 0x7F); }
void Core::RES7D() { registers->setD(registers->getD() & 0x7F); }
void Core::RES7E() { registers->setE(registers->getE() & 0x7F); }
void Core::RES7H() { registers->setH(registers->getH() & 0x7F); }
void Core::RES7L() { registers->setL(registers->getL() & 0x7F); }
void Core::RES7HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) & 0x7F); }

void Core::SET0A() { registers->setA(registers->getA() | 0x01); }
void Core::SET0B() { registers->setB(registers->getB() | 0x01); }
void Core::SET0C() { registers->setC(registers->getC() | 0x01); }
void Core::SET0D() { registers->setD(registers->getD() | 0x01); }
void Core::SET0E() { registers->setE(registers->getE() | 0x01); }
void Core::SET0H() { registers->setH(registers->getH() | 0x01); }
void Core::SET0L() { registers->setL(registers->getL() | 0x01); }
void Core::SET0HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) | 0x01); }

void Core::SET1A() { registers->setA(registers->getA() | 0x02); }
void Core::SET1B() { registers->setB(registers->getB() | 0x02); }
void Core::SET1C() { registers->setC(registers->getC() | 0x02); }
void Core::SET1D() { registers->setD(registers->getD() | 0x02); }
void Core::SET1E() { registers->setE(registers->getE() | 0x02); }
void Core::SET1H() { registers->setH(registers->getH() | 0x02); }
void Core::SET1L() { registers->setL(registers->getL() | 0x02); }
void Core::SET1HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) | 0x02); }

void Core::SET2A() { registers->setA(registers->getA() | 0x04); }
void Core::SET2B() { registers->setB(registers->getB() | 0x04); }
void Core::SET2C() { registers->setC(registers->getC() | 0x04); }
void Core::SET2D() { registers->setD(registers->getD() | 0x04); }
void Core::SET2E() { registers->setE(registers->getE() | 0x04); }
void Core::SET2H() { registers->setH(registers->getH() | 0x04); }
void Core::SET2L() { registers->setL(registers->getL() | 0x04); }
void Core::SET2HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) | 0x04); }

void Core::SET3A() { registers->setA(registers->getA() | 0x08); }
void Core::SET3B() { registers->setB(registers->getB() | 0x08); }
void Core::SET3C() { registers->setC(registers->getC() | 0x08); }
void Core::SET3D() { registers->setD(registers->getD() | 0x08); }
void Core::SET3E() { registers->setE(registers->getE() | 0x08); }
void Core::SET3H() { registers->setH(registers->getH() | 0x08); }
void Core::SET3L() { registers->setL(registers->getL() | 0x08); }
void Core::SET3HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) | 0x08); }

void Core::SET4A() { registers->setA(registers->getA() | 0x10); }
void Core::SET4B() { registers->setB(registers->getB() | 0x10); }
void Core::SET4C() { registers->setC(registers->getC() | 0x10); }
void Core::SET4D() { registers->setD(registers->getD() | 0x10); }
void Core::SET4E() { registers->setE(registers->getE() | 0x10); }
void Core::SET4H() { registers->setH(registers->getH() | 0x10); }
void Core::SET4L() { registers->setL(registers->getL() | 0x10); }
void Core::SET4HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) | 0x10); }

void Core::SET5A() { registers->setA(registers->getA() | 0x20); }
void Core::SET5B() { registers->setB(registers->getB() | 0x20); }
void Core::SET5C() { registers->setC(registers->getC() | 0x20); }
void Core::SET5D() { registers->setD(registers->getD() | 0x20); }
void Core::SET5E() { registers->setE(registers->getE() | 0x20); }
void Core::SET5H() { registers->setH(registers->getH() | 0x20); }
void Core::SET5L() { registers->setL(registers->getL() | 0x20); }
void Core::SET5HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) | 0x20); }

void Core::SET6A() { registers->setA(registers->getA() | 0x40); }
void Core::SET6B() { registers->setB(registers->getB() | 0x40); }
void Core::SET6C() { registers->setC(registers->getC() | 0x40); }
void Core::SET6D() { registers->setD(registers->getD() | 0x40); }
void Core::SET6E() { registers->setE(registers->getE() | 0x40); }
void Core::SET6H() { registers->setH(registers->getH() | 0x40); }
void Core::SET6L() { registers->setL(registers->getL() | 0x40); }
void Core::SET6HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) | 0x40); }

void Core::SET7A() { registers->setA(registers->getA() | 0x80); }
void Core::SET7B() { registers->setB(registers->getB() | 0x80); }
void Core::SET7C() { registers->setC(registers->getC() | 0x80); }
void Core::SET7D() { registers->setD(registers->getD() | 0x80); }
void Core::SET7E() { registers->setE(registers->getE() | 0x80); }
void Core::SET7H() { registers->setH(registers->getH() | 0x80); }
void Core::SET7L() { registers->setL(registers->getL() | 0x80); }
void Core::SET7HL() { memory->write(registers->getHL(), memory->read(registers->getHL()) | 0x80); }
}
