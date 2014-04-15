// Copyright (c) 2014 Jan Böker
// MIT License

#ifndef GAMEBOY_CPUREGISTERS_H
#define GAMEBOY_CPUREGISTERS_H

#include <cinttypes>

namespace gameboy {
class CPURegisters {
 public:
    CPURegisters();
    virtual ~CPURegisters();
    void reset();

    void setA(uint8_t value);
    void setB(uint8_t value);
    void setC(uint8_t value);
    void setD(uint8_t value);
    void setE(uint8_t value);
    void setF(uint8_t value);
    void setH(uint8_t value);
    void setL(uint8_t value);
    uint8_t getA() const;
    uint8_t getB() const;
    uint8_t getC() const;
    uint8_t getD() const;
    uint8_t getE() const;
    uint8_t getF() const;
    uint8_t getH() const;
    uint8_t getL() const;

    void setAF(uint16_t value);
    void setBC(uint16_t value);
    void setDE(uint16_t value);
    void setHL(uint16_t value);
    uint16_t getAF() const;
    uint16_t getBC() const;
    uint16_t getDE() const;
    uint16_t getHL() const;

    void setZeroFlag(bool flag);
    void setSubFlag(bool flag);
    void setHalfCarryFlag(bool flag);
    void setCarryFlag(bool flag);
    bool getZeroFlag() const;
    bool getSubFlag() const;
    bool getHalfCarryFlag() const;
    bool getCarryFlag() const;

    void setSP(uint16_t value);
    uint16_t getSP() const;

    void setIME(bool flag);
    bool getIME();

    uint16_t pc;

 private:
    void setFlag(unsigned int bitpos, bool flag);
    bool getFlag(unsigned int bitpos) const;

    bool interruptMasterEnable;
    uint8_t *registers;
    uint16_t stackPointer;
};
}

#endif
