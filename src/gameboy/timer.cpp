#include "timer.h"

#include <cinttypes>
#include <QDebug>
#include "memory.h"

namespace gameboy {
Timer::Timer(Memory *memory) :
    memory(memory) {
        reset();
}

Timer::~Timer() {
}

void Timer::reset() {
    clocks = 0;
    main = 0;
    dividerHelper = 0;
}

void Timer::step(unsigned int lastClocks) {
    clocks += lastClocks;

    while (clocks >= 4) {
        main++;
        clocks -= 4;

        dividerHelper++;
        if (dividerHelper == 16) {
            memory->writeRaw(0xFF04, memory->read(0xFF04) + 1);
            dividerHelper = 0;
        }

        uint8_t timerControl = memory->read(0xFF07);
        if (timerControl & 0x04) { // Running
            unsigned int threshold = 0;
            switch (timerControl & 0x03) {
                case 0:
                    threshold = 64; // 4096Hz
                break;
                case 1:
                    threshold = 1; // 262144Hz
                break;
                case 2:
                    threshold = 4; // 65536Hz
                break;
                case 3:
                    threshold = 16; // 16384Hz
                break;
                default:
                break;
            }

            if (main >= threshold) {
                stepCounter();
            }
        }
    }
}

void Timer::stepCounter() {
    main = 0;
    uint8_t counter = memory->read(0xFF05);

    if (counter == 0xFF) {
        memory->write(0xFF05, memory->read(0xFF06));
        memory->write(0xFF0F, memory->read(0xFF0F) | 0x04); //Set Timer Interrupt Flag
    } else {
        memory->write(0xFF05, counter + 1);
    }
}
}