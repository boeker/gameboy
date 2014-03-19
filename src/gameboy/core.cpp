#include "core.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <QDebug>
#include "cpuregisters.h"
#include "keyboard.h"
#include "memory.h"
#include "screen.h"

namespace gameboy {
Core::Core() :
    registers(new CPURegisters),
    memory(new Memory),
    breakpoint(0),
    screen(new Screen(memory)),
    keyboard(new Keyboard),
    lastClocks(0),
    clock(0) {
}

Core::~Core() {
    delete keyboard;
    delete screen;
    delete memory;
    delete registers;
}

void Core::loadROM(const std::string &file) {
    memory->loadROM(file);
}

void Core::reset() {
    registers->reset();
    memory->reset();
    screen->reset();
    lastClocks = 0;
    clock = 0;
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
    uint8_t interrupt = memory->read(0xFF0F) & memory->read(0xFFFF) & 0x1F;
    if (registers->getIME() && interrupt) {
        if (interrupt & 0x01) { // V-BLANK
            memory->write(0xFF0F, memory->read(0xFF0F) & 0xFE); // Disable Flag
            INT40();
        } else if (interrupt & 0x02) { // LCD-STAT
            memory->write(0xFF0F, memory->read(0xFF0F) & 0xFD); // Disable Flag
            INT48();
        } else if (interrupt & 0x04) { // TIMER
            memory->write(0xFF0F, memory->read(0xFF0F) & 0xFB); // Disable Flag
            INT50();
        } else if (interrupt & 0x08) { // SERIAL
            memory->write(0xFF0F, memory->read(0xFF0F) & 0xF7); // Disable Flag
            INT58();
        } else if (interrupt & 0x10) { // JOYPAD
            memory->write(0xFF0F, memory->read(0xFF0F) & 0xEF); // Disable Flag
            INT60();
        }
    } else {
        (this->*opCodes[memory->read(registers->pc++)])();
    }

    clock += lastClocks;
    screen->step(lastClocks);
    updateKeyRegister();
}

void Core::handleCB() {
    (this->*opCodesCB[memory->read(registers->pc++)])();
}

void Core::xx() {
    qDebug() << "Unknown opcode: " << QString("%1").arg(memory->read(registers->pc-1), 0, 16);
    exit(EXIT_FAILURE);
}

void Core::CBxx() {
    qDebug() << "Unknown opcode: cb" << QString("%1").arg(memory->read(registers->pc-1), 0, 16);
    exit(EXIT_FAILURE);
}

void Core::emulateUntilVBlank() {
    do {
        if (breakpoint != 0 && breakpoint == registers->pc) {
            qDebug() << "Breaking, press pause";
            return;
        }
        emulateCycle();
    } while (!screen->drawFlagSet());
}

void Core::updateKeyRegister() { //Keys are active-low
    if ((memory->read(0xFF00) & 0x20) == 0) { //Bit 5
        if (keyboard->start) {
            if (memory->read(0xFF00) & 0x08) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x10);
            }
            memory->write(0xFF00, memory->read(0xFF00) & 0xF7);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x08);
        }
        if (keyboard->select) {
            if (memory->read(0xFF00) & 0x04) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x10);
            }
            memory->write(0xFF00, memory->read(0xFF00) & 0xFB);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x04);
        }
        if (keyboard->b) {
            if (memory->read(0xFF00) & 0x02) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x10);
            }
            memory->write(0xFF00, memory->read(0xFF00) & 0xFD);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x02);
        }
        if (keyboard->a) {
            if (memory->read(0xFF00) & 0x01) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x10);
            }
            memory->write(0xFF00, memory->read(0xFF00) & 0xFE);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x01);
        }
    } else if ((memory->read(0xFF00) & 0x10) == 0) { //Bit 4
        if (keyboard->down) {
            if (memory->read(0xFF00) & 0x08) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x10);
            }
            memory->write(0xFF00, memory->read(0xFF00) & 0xF7);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x08);
        }
        if (keyboard->up) {
            if (memory->read(0xFF00) & 0x04) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x10);
            }
            memory->write(0xFF00, memory->read(0xFF00) & 0xFB);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x04);
        }
        if (keyboard->left) {
            if (memory->read(0xFF00) & 0x02) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x10);
            }
            memory->write(0xFF00, memory->read(0xFF00) & 0xFD);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x02);
        }
        if (keyboard->right) {
            if (memory->read(0xFF01) & 0x08) {
                memory->write(0xFF0F, memory->read(0xFF0F) | 0x10);
            }
            memory->write(0xFF00, memory->read(0xFF00) & 0xFE);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x01);
        }
    }
}
}
