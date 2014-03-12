#include "core.h"

namespace gameboy {
const Core::opCode Core::opCodes[] = {
    //00
    &Core::NOP,      &Core::LDBCnn,   &Core::LDBCMA,   &Core::INCBC,
    &Core::INCrB,    &Core::DECrB,    &Core::LDrnB,    &Core::RLCA,
    &Core::LDnnSP,   &Core::ADDHLBC,  &Core::LDABCM,   &Core::DECBC,
    &Core::INCrC,    &Core::DECrC,    &Core::LDrnC,    &Core::RRCA,
    //10
    &Core::xx,       &Core::LDDEnn,   &Core::LDDEMA,   &Core::INCDE,
    &Core::INCrD,    &Core::DECrD,    &Core::LDrnD,    &Core::xx,
    &Core::JRn,      &Core::ADDHLDE,  &Core::LDADEM,   &Core::DECDE,
    &Core::INCrE,    &Core::DECrE,    &Core::LDrnE,    &Core::RRANCB,
    //20
    &Core::JRNZn,    &Core::LDHLnn,   &Core::LDIHLA,   &Core::INCHL,
    &Core::INCrH,    &Core::DECrH,    &Core::LDrnH,    &Core::xx,
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
    &Core::xx,       &Core::xx,       &Core::LDAmm,    &Core::EI,
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
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CB30
    &Core::SWAPrB,   &Core::SWAPrC,   &Core::SWAPrD,   &Core::SWAPrE,
    &Core::SWAPrH,   &Core::SWAPrL,   &Core::SWAPrHLm, &Core::SWAPrA,
    &Core::SRLB,     &Core::SRLC,     &Core::SRLD,     &Core::SRLE,
    &Core::SRLH,     &Core::SRLL,     &Core::SRLHL,     &Core::SRLA,
    //CB40
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CB50
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CB60
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CB70
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CB80
    &Core::RES0B,    &Core::RES0C,    &Core::RES0D,    &Core::RES0E,
    &Core::RES0H,    &Core::RES0L,    &Core::RES0HL,   &Core::RES0A,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CB90
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CBA0
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CBB0
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CBC0
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CBD0
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CBE0
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    //CBF0
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
    &Core::CBxx,     &Core::CBxx,     &Core::CBxx,     &Core::CBxx,
};
}
