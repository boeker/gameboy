#ifndef GAMEBOY_CORE_H
#define GAMEBOY_CORE_H

#include <cstdlib>
#include <string>

namespace util {
class Color;
}

namespace gameboy {
class CPURegisters;
class Keyboard;
class Memory;
class Screen;
}

namespace gameboy {
class Core {
 public:
    explicit Core(const std::string &);
    virtual ~Core();

    Keyboard* getKeyboard();
    util::Color* getFramebuffer();
    bool drawFlagSet();

    void emulateCycle();
    void emulateUntilVBlank();
    void updateKeyRegister();

    void opcdump();
    void regdump();
    void sysdump();

 private:
    CPURegisters *registers;
    Memory *memory;
    Screen *screen;
    Keyboard *keyboard;

    unsigned int lastClocks;
    unsigned int clock;

    typedef void (Core::*opCode) ();
    static const opCode opCodes[];
    static const opCode opCodesCB[];

 private:
    void handleCB();
    void xx();
    void CBxx();
    void LDrnA();
    void LDrnB();
    void LDrnC();
    void LDrnD();
    void LDrnE();
    void LDrnH();
    void LDrnL();
    void LDrrAA();
    void LDrrAB();
    void LDrrAC();
    void LDrrAD();
    void LDrrAE();
    void LDrrAH();
    void LDrrAL();
    void LDrrBA();
    void LDrrBB();
    void LDrrBC();
    void LDrrBD();
    void LDrrBE();
    void LDrrBH();
    void LDrrBL();
    void LDrrCA();
    void LDrrCB();
    void LDrrCC();
    void LDrrCD();
    void LDrrCE();
    void LDrrCH();
    void LDrrCL();
    void LDrrDA();
    void LDrrDB();
    void LDrrDC();
    void LDrrDD();
    void LDrrDE();
    void LDrrDH();
    void LDrrDL();
    void LDrrEA();
    void LDrrEB();
    void LDrrEC();
    void LDrrED();
    void LDrrEE();
    void LDrrEH();
    void LDrrEL();
    void LDrrHA();
    void LDrrHB();
    void LDrrHC();
    void LDrrHD();
    void LDrrHE();
    void LDrrHH();
    void LDrrHL();
    void LDrrLA();
    void LDrrLB();
    void LDrrLC();
    void LDrrLD();
    void LDrrLE();
    void LDrrLH();
    void LDrrLL();
    void LDrHLMA();
    void LDrHLMB();
    void LDrHLMC();
    void LDrHLMD();
    void LDrHLME();
    void LDrHLMH();
    void LDrHLML();
    void LDABCM();
    void LDADEM();
    void LDAmm();
    void LDHLMrA();
    void LDHLMrB();
    void LDHLMrC();
    void LDHLMrD();
    void LDHLMrE();
    void LDHLMrH();
    void LDHLMrL();
    void LDHLmn();
    void LDBCMA();
    void LDDEMA();
    void LDnnA();
    void LDDHLA();
    void LDDAHL();
    void LDIHLA();
    void LDIAHL();
    void LDIOnA();
    void LDAIOn();
    void LDIOCA();
    void LDAIOC();
    void LDBCnn();
    void LDDEnn();
    void LDHLnn();
    void LDSPnn();
    void LDnnSP();
    void ADDrA();
    void ADDrB();
    void ADDrC();
    void ADDrD();
    void ADDrE();
    void ADDrH();
    void ADDrL();
    void ADDHLM();
    void ADDn();
    void ADCrA();
    void ADCrB();
    void ADCrC();
    void ADCrD();
    void ADCrE();
    void ADCrH();
    void ADCrL();
    void ADCHLM();
    void ADCn();
    void SUBrA();
    void SUBrB();
    void SUBrC();
    void SUBrD();
    void SUBrE();
    void SUBrH();
    void SUBrL();
    void SUBHLM();
    void SUBn();
    void SBCrA();
    void SBCrB();
    void SBCrC();
    void SBCrD();
    void SBCrE();
    void SBCrH();
    void SBCrL();
    void SBCHLM();
    void SBCn();
    void ANDrA();
    void ANDrB();
    void ANDrC();
    void ANDrD();
    void ANDrE();
    void ANDrH();
    void ANDrL();
    void ANDHLM();
    void ANDn();
    void ORrA();
    void ORrB();
    void ORrC();
    void ORrD();
    void ORrE();
    void ORrH();
    void ORrL();
    void ORHLM();
    void ORn();
    void XORrA();
    void XORrB();
    void XORrC();
    void XORrD();
    void XORrE();
    void XORrH();
    void XORrL();
    void XORHLM();
    void XORn();
    void CPrA();
    void CPrB();
    void CPrC();
    void CPrD();
    void CPrE();
    void CPrH();
    void CPrL();
    void CPHLM();
    void CPn();
    void INCrA();
    void INCrB();
    void INCrC();
    void INCrD();
    void INCrE();
    void INCrH();
    void INCrL();
    void INCHLM();
    void DECrA();
    void DECrB();
    void DECrC();
    void DECrD();
    void DECrE();
    void DECrH();
    void DECrL();
    void DECHLM();
    void INCBC();
    void INCDE();
    void INCHL();
    void INCSP();
    void DECBC();
    void DECDE();
    void DECHL();
    void DECSP();
    void ADDHLBC();
    void ADDHLDE();
    void ADDHLHL();
    void ADDHLSP();
    void ADDSPn();
    void JPnn();
    void JPHL();
    void JPNZnn();
    void JPZnn();
    void JPNCnn();
    void JPCnn();
    void JRn();
    void JRNZn();
    void JRZn();
    void JRNCn();
    void JRCn();
    void CALLnn();
    void CALLNZnn();
    void CALLZnn();
    void CALLNCnn();
    void CALLCnn();
    void RET();
    void RETI();
    void RETNZ();
    void RETZ();
    void RETNC();
    void RETC();
    void PUSHAF();
    void PUSHBC();
    void PUSHDE();
    void PUSHHL();
    void POPAF();
    void POPBC();
    void POPDE();
    void POPHL();
    void RST00();
    void RST08();
    void RST10();
    void RST18();
    void RST20();
    void RST28();
    void RST30();
    void RST38();
    void NOP();
    void DI();
    void EI();
    void STOP();
    void SCF();
    void CPL();
    void RRCA();
    void RLCA();
    void SWAPrA();
    void SWAPrB();
    void SWAPrC();
    void SWAPrD();
    void SWAPrE();
    void SWAPrH();
    void SWAPrL();
    void SWAPrHLm();
    void RLCB();
    void RLCC();
    void RLCD();
    void RLCE();
    void RLCH();
    void RLCL();
    void RLCHLM();
    void RLA();
    void RLB();
    void RLC();
    void RLD();
    void RLE();
    void RLH();
    void RLL();
    void RLHLM();
    void RRA();
    void RRB();
    void RRC();
    void RRD();
    void RRE();
    void RRH();
    void RRL();
    void RRHLM();
    void RES0A();
    void RES0B();
    void RES0C();
    void RES0D();
    void RES0E();
    void RES0H();
    void RES0L();
    void RES0HL();
};
}

#endif
