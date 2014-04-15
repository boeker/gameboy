// Copyright (c) 2014 Jan Böker
// MIT License

#include "mbc3tim.h"

#include <QDebug>
#include <cstring>
#include <ctime>
#include <fstream>

namespace gameboy {
namespace mbc {
MBC3TIM::MBC3TIM(uint8_t **romBanks, uint8_t numBanks, const std::string& rtc) :
    MBC3(romBanks, numBanks),
    enabled(false),
    timEnabled(false),
    currentRegister(0),
    rtcFile(rtc) {
    rtcRegisters = new uint8_t[5];
    memset(rtcRegisters, 0, 5);


    std::ifstream rtcStream(rtcFile, std::ios::binary);
    if (rtcStream.good()) {
            rtcStream.read(reinterpret_cast<char*>(&dayCounterStart), sizeof dayCounterStart);
    } else {
        dayCounterStart = time(0);
    }
}

MBC3TIM::~MBC3TIM() {
    std::ofstream rtcStream(rtcFile, std::ios::binary);
    rtcStream.write(reinterpret_cast<const char*>(&dayCounterStart), sizeof dayCounterStart);

    delete[] rtcRegisters;
}

void MBC3TIM::write(uint16_t address, uint8_t value) {
    if (address <= 0x1FFF) {
        enabled = (value & 0x0A) == 0x0A;
    } else if (address >= 0x4000 && address <= 0x5FFF) {
        // Map RTC register
        currentRegister = value - 0x08;
    } else if (address >= 0x6000 && address <= 0x7FFF) { // Latch Clock Data
        // 00 -> 01 => Latch current time into the RTC registers
        time_t currentTime = time(0);
        struct tm* localTime = localtime(&currentTime);
        unsigned int currentDays = daysSince1900(localTime);
        rtcRegisters[0] = localTime->tm_sec % 60;
        rtcRegisters[1] = localTime->tm_min;
        rtcRegisters[2] = localTime->tm_hour;

        unsigned int counterStartDays = daysSince1900(localtime(&dayCounterStart));
        int diffDays = currentDays - counterStartDays;

        rtcRegisters[3] = diffDays & 0xFF;
        rtcRegisters[4] = (diffDays & 0x100) >> 8;
        if (diffDays > 0x1FF) {
            rtcRegisters[4] |= 0x80;
        }
    } else {
        MBC3::write(address, value);
    }
}

void MBC3TIM::writeRAM(uint16_t, uint8_t value) {
    if (enabled && currentRegister < 5) {
        rtcRegisters[currentRegister] = value;
        if (currentRegister == 3 || (currentRegister == 4 && ((value & 0x01) != (rtcRegisters[4] & 0x01)))) {
            time_t currentTime = time(0);
            uint16_t days = ((rtcRegisters[4] & 0x1) << 8) || rtcRegisters[3];
            dayCounterStart = currentTime - days*24*60*60;
        }
    }
}

uint8_t MBC3TIM::readRAM(uint16_t) {
    return (enabled && currentRegister < 5) ? rtcRegisters[currentRegister] : 0;
}

unsigned int MBC3TIM::daysSince1900(struct tm *date) {
    unsigned int days = 0;
    for (int year = 0; year < date->tm_year; ++year) {
        if (((year+1900) % 4) == 0 && (((year+1900) % 100) != 0 || ((year+1900) % 400) == 0)) {
            days += 366;
        } else {
            days += 365;
        }
    }
    return days + date->tm_yday;
}
}
}