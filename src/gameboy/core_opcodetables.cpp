#include "core.h"

namespace gameboy {
const Core::opCode Core::opCodes[] = {
    //00
    &Core::NOP,      &Core::LDBCnn,   &Core::LDBCMA,   &Core::INCBC,
    &Core::INCrB,    &Core::DECrB,    &Core::LDrnB,    &Core::RLCA,
    &Core::LDnnSP,   &Core::ADDHLBC,  &Core::LDABCM,   &Core::DECBC,
    &Core::INCrC,    &Core::DECrC,    &Core::LDrnC,    &Core::RRCA,
    //10
    &Core::STOP,     &Core::LDDEnn,   &Core::LDDEMA,   &Core::INCDE,
    &Core::INCrD,    &Core::DECrD,    &Core::LDrnD,    &Core::xx,
    &Core::JRn,      &Core::ADDHLDE,  &Core::LDADEM,   &Core::DECDE,
    &Core::INCrE,    &Core::DECrE,    &Core::LDrnE,    &Core::RRANCB,
    //20
    &Core::JRNZn,    &Core::LDHLnn,   &Core::LDIHLA,   &Core::INCHL,
    &Core::INCrH,    &Core::DECrH,    &Core::LDrnH,    &Core::DAA,
    &Core::JRZn,     &Core::ADDHLHL,  &Core::LDIAHL,   &Core::DECHL,
    &Core::INCrL,    &Core::DECrL,    &Core::LDrnL,    &Core::CPL,
    //30
    &Core::JRNCn,    &Core::LDSPnn,   &Core::LDDHLA,   &Core::INCSP,
    &Core::INCHLM,   &Core::DECHLM,   &Core::LDHLmn,   &Core::SCF,
    &Core::JRCn,     &Core::ADDHLSP,  &Core::LDDAHL,   &Core::DECSP,
    &Core::INCrA,    &Core::DECrA,    &Core::LDrnA,    &Core::xx,
    //40
    &Core::LDrrBB,   &Core::LDrrBC,   &Core::LDrrBD,   &Core::LDrrBE,
    &Core::LDrrBH,   &Core::LDrrBL,   &Core::LDrHLMB,  &Core::LDrrBA,
    &Core::LDrrCB,   &Core::LDrrCC,   &Core::LDrrCD,   &Core::LDrrCE,
    &Core::LDrrCH,   &Core::LDrrCL,   &Core::LDrHLMC,  &Core::LDrrCA,
    //50
    &Core::LDrrDB,   &Core::LDrrDC,   &Core::LDrrDD,   &Core::LDrrDE,
    &Core::LDrrDH,   &Core::LDrrDL,   &Core::LDrHLMD,  &Core::LDrrDA,
    &Core::LDrrEB,   &Core::LDrrEC,   &Core::LDrrED,   &Core::LDrrEE,
    &Core::LDrrEH,   &Core::LDrrEL,   &Core::LDrHLME,  &Core::LDrrEA,
    //60
    &Core::LDrrHB,   &Core::LDrrHC,   &Core::LDrrHD,   &Core::LDrrHE,
    &Core::LDrrHH,   &Core::LDrrHL,   &Core::LDrHLMH,  &Core::LDrrHA,
    &Core::LDrrLB,   &Core::LDrrLC,   &Core::LDrrLD,   &Core::LDrrLE,
    &Core::LDrrLH,   &Core::LDrrLL,   &Core::LDrHLML,  &Core::LDrrLA,
    //70
    &Core::LDHLMrB,  &Core::LDHLMrC,  &Core::LDHLMrD,  &Core::LDHLMrE,
    &Core::LDHLMrH,  &Core::LDHLMrL,  &Core::xx,       &Core::LDHLMrA,
    &Core::LDrrAB,   &Core::LDrrAC,   &Core::LDrrAD,   &Core::LDrrAE,
    &Core::LDrrAH,   &Core::LDrrAL,   &Core::LDrHLMA,  &Core::LDrrAA,
    //80
    &Core::ADDrB,    &Core::ADDrC,    &Core::ADDrD,    &Core::ADDrE,
    &Core::ADDrH,    &Core::ADDrL,    &Core::ADDHLM,   &Core::ADDrA,
    &Core::ADCrB,    &Core::ADCrC,    &Core::ADCrD,    &Core::ADCrE,
    &Core::ADCrH,    &Core::ADCrL,    &Core::ADCHLM,   &Core::ADCrA,
    //90
    &Core::SUBrB,    &Core::SUBrC,    &Core::SUBrD,    &Core::SUBrE,
    &Core::SUBrH,    &Core::SUBrL,    &Core::SUBHLM,   &Core::SUBrA,
    &Core::SBCrB,    &Core::SBCrC,    &Core::SBCrD,    &Core::SBCrE,
    &Core::SBCrH,    &Core::SBCrL,    &Core::SBCHLM,   &Core::SBCrA,
    //A0
    &Core::ANDrB,    &Core::ANDrC,    &Core::ANDrD,    &Core::ANDrE,
    &Core::ANDrH,    &Core::ANDrL,    &Core::ANDHLM,   &Core::ANDrA,
    &Core::XORrB,    &Core::XORrC,    &Core::XORrD,    &Core::XORrE,
    &Core::XORrH,    &Core::XORrL,    &Core::XORHLM,   &Core::XORrA,
    //B0
    &Core::ORrB,     &Core::ORrC,     &Core::ORrD,     &Core::ORrE,
    &Core::ORrH,     &Core::ORrL,     &Core::ORHLM,    &Core::ORrA,
    &Core::CPrB,     &Core::CPrC,     &Core::CPrD,     &Core::CPrE,
    &Core::CPrH,     &Core::CPrL,     &Core::CPHLM,    &Core::CPrA,
    //C0
    &Core::RETNZ,    &Core::POPBC,    &Core::JPNZnn,   &Core::JPnn,
    &Core::CALLNZnn, &Core::PUSHBC,   &Core::ADDn,     &Core::RST00,
    &Core::RETZ,     &Core::RET,      &Core::JPZnn,    &Core::handleCB,
    &Core::CALLZnn,  &Core::CALLnn,   &Core::ADCn,     &Core::RST08,
    //D0
    &Core::RETNC,    &Core::POPDE,    &Core::JPNCnn,   &Core::xx,
    &Core::CALLNCnn, &Core::PUSHDE,   &Core::SUBn,     &Core::RST10,
    &Core::RETC,     &Core::RETI,     &Core::JPCnn,    &Core::xx,
    &Core::CALLCnn,  &Core::xx,       &Core::SBCn,     &Core::RST18,
    //E0
    &Core::LDIOnA,   &Core::POPHL,    &Core::LDIOCA,   &Core::xx,
    &Core::xx,       &Core::PUSHHL,   &Core::ANDn,     &Core::RST20,
    &Core::ADDSPn,   &Core::JPHL,     &Core::LDnnA,    &Core::xx,
    &Core::xx,       &Core::xx,       &Core::XORn,     &Core::RST28,
    //F0
    &Core::LDAIOn,   &Core::POPAF,    &Core::LDAIOC,   &Core::DI,
    &Core::xx,       &Core::PUSHAF,   &Core::ORn,      &Core::RST30,
    &Core::LDHLSPn,  &Core::LDSPHL,   &Core::LDAmm,    &Core::EI,
    &Core::xx,       &Core::xx,       &Core::CPn,      &Core::RST38,
};

const Core::opCode Core::opCodesCB[] = {
    //CB00
    &Core::RLCB,     &Core::RLCC,     &Core::RLCD,     &Core::RLCE,
    &Core::RLCH,     &Core::RLCL,     &Core::RLCHLM,   &Core::RLCA,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CB10
    &Core::RLB,      &Core::RLC,      &Core::RLD,      &Core::RLE,
    &Core::RLH,      &Core::RLL,      &Core::RLHLM,    &Core::RLA,
    &Core::RRB,      &Core::RRC,      &Core::RRD,      &Core::RRE,
    &Core::RRH,      &Core::RRL,      &Core::RRHLM,    &Core::RRA,
    //CB20
    &Core::SLAB,     &Core::SLAC,     &Core::SLAD,     &Core::SLAE,
    &Core::SLAH,     &Core::SLAL,     &Core::SLAHL,    &Core::SLAA,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CB30
    &Core::SWAPrB,   &Core::SWAPrC,   &Core::SWAPrD,   &Core::SWAPrE,
    &Core::SWAPrH,   &Core::SWAPrL,   &Core::SWAPrHLm, &Core::SWAPrA,
    &Core::SRLB,     &Core::SRLC,     &Core::SRLD,     &Core::SRLE,
    &Core::SRLH,     &Core::SRLL,     &Core::SRLHL,    &Core::SRLA,
    //CB40
    &Core::BIT0B,    &Core::BIT0C,    &Core::BIT0D,    &Core::BIT0E,
    &Core::BIT0H,    &Core::BIT0L,    &Core::BIT0HL,   &Core::BIT0A,
    &Core::BIT1B,    &Core::BIT1C,    &Core::BIT1D,    &Core::BIT1E,
    &Core::BIT1H,    &Core::BIT1L,    &Core::BIT1HL,   &Core::BIT1A,
    //CB50
    &Core::BIT2B,    &Core::BIT2C,    &Core::BIT2D,    &Core::BIT2E,
    &Core::BIT2H,    &Core::BIT2L,    &Core::BIT2L,    &Core::BIT2A,
    &Core::BIT3B,    &Core::BIT3C,    &Core::BIT3D,    &Core::BIT3E,
    &Core::BIT3H,    &Core::BIT3L,    &Core::BIT3HL,   &Core::BIT3A,
    //CB60
    &Core::BIT4B,    &Core::BIT4C,    &Core::BIT4D,    &Core::BIT4E,
    &Core::BIT4H,    &Core::BIT4L,    &Core::BIT4HL,   &Core::BIT4A,
    &Core::BIT5B,    &Core::BIT5C,    &Core::BIT5D,    &Core::BIT5E,
    &Core::BIT5H,    &Core::BIT5L,    &Core::BIT5HL,   &Core::BIT5A,
    //CB70
    &Core::BIT6B,    &Core::BIT6C,    &Core::BIT6D,    &Core::BIT6E,
    &Core::BIT6H,    &Core::BIT6L,    &Core::BIT6HL,   &Core::BIT6A,
    &Core::BIT7B,    &Core::BIT7C,    &Core::BIT7D,    &Core::BIT7E,
    &Core::BIT7H,    &Core::BIT7L,    &Core::BIT7HL,   &Core::BIT7A,
    //CB80
    &Core::RES0B,    &Core::RES0C,    &Core::RES0D,    &Core::RES0E,
    &Core::RES0H,    &Core::RES0L,    &Core::RES0HL,   &Core::RES0A,
    &Core::RES1B,    &Core::RES1C,    &Core::RES1D,    &Core::RES1E,
    &Core::RES1H,    &Core::RES1L,    &Core::RES1HL,   &Core::RES1A,
    //CB90
    &Core::RES2B,    &Core::RES2C,    &Core::RES2D,    &Core::RES2E,
    &Core::RES2H,    &Core::RES2L,    &Core::RES2HL,   &Core::RES2A,
    &Core::RES3B,    &Core::RES3C,    &Core::RES3D,    &Core::RES3E,
    &Core::RES3H,    &Core::RES3L,    &Core::RES3HL,   &Core::RES3A,
    //CBA0
    &Core::RES4B,    &Core::RES4C,    &Core::RES4D,    &Core::RES4E,
    &Core::RES4H,    &Core::RES4L,    &Core::RES4HL,   &Core::RES4A,
    &Core::RES5B,    &Core::RES5C,    &Core::RES5D,    &Core::RES5E,
    &Core::RES5H,    &Core::RES5L,    &Core::RES5HL,   &Core::RES5A,
    //CBB0
    &Core::RES6B,    &Core::RES6C,    &Core::RES6D,    &Core::RES6E,
    &Core::RES6H,    &Core::RES6L,    &Core::RES6HL,   &Core::RES6A,
    &Core::RES7B,    &Core::RES7C,    &Core::RES7D,    &Core::RES7E,
    &Core::RES7H,    &Core::RES7L,    &Core::RES7HL,   &Core::RES7A,
    //CBC0
    &Core::SET0B,    &Core::SET0C,    &Core::SET0D,    &Core::SET0E,
    &Core::SET0H,    &Core::SET0L,    &Core::SET0HL,   &Core::SET0A,
    &Core::SET1B,    &Core::SET1C,    &Core::SET1D,    &Core::SET1E,
    &Core::SET1H,    &Core::SET1L,    &Core::SET1HL,   &Core::SET1A,
    //CBD0
    &Core::SET2B,    &Core::SET2C,    &Core::SET2D,    &Core::SET2E,
    &Core::SET2H,    &Core::SET2L,    &Core::SET2HL,   &Core::SET2A,
    &Core::SET3B,    &Core::SET3C,    &Core::SET3D,    &Core::SET3E,
    &Core::SET3H,    &Core::SET3L,    &Core::SET3HL,   &Core::SET3A,
    //CBE0
    &Core::SET4B,    &Core::SET4C,    &Core::SET4D,    &Core::SET4E,
    &Core::SET4H,    &Core::SET4L,    &Core::SET4HL,   &Core::SET4A,
    &Core::SET5B,    &Core::SET5C,    &Core::SET5D,    &Core::SET5E,
    &Core::SET5H,    &Core::SET5L,    &Core::SET5HL,   &Core::SET5A,
    //CBF0
    &Core::SET6B,    &Core::SET6C,    &Core::SET6D,    &Core::SET6E,
    &Core::SET6H,    &Core::SET6L,    &Core::SET6HL,   &Core::SET6A,
    &Core::SET7B,    &Core::SET7C,    &Core::SET7D,    &Core::SET7E,
    &Core::SET7H,    &Core::SET7L,    &Core::SET7HL,   &Core::SET7A,
};
}
