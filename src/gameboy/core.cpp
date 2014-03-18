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
    uint8_t interrupt = memory->read(0xFF0F) & memory->read(0xFFFF);
    if (registers->getIME() && interrupt) {
        if (interrupt & 0x01) { // V-BLANK
            memory->write(0xFF0F, memory->read(0xFF0F) & 0xFE); // Disable Flag
            INT40();
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
        emulateCycle();
    } while (!screen->drawFlagSet());
}

void Core::updateKeyRegister() { //Keys are active-low
    if ((memory->read(0xFF00) & 0x20) == 0) { //Bit 5
        if (keyboard->start) {
            memory->write(0xFF00, memory->read(0xFF00) & 0xF7);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x08);
        }
        if (keyboard->select) {
            memory->write(0xFF00, memory->read(0xFF00) & 0xFB);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x04);
        }
        if (keyboard->b) {
            memory->write(0xFF00, memory->read(0xFF00) & 0xFD);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x02);
        }
        if (keyboard->a) {
            memory->write(0xFF00, memory->read(0xFF00) & 0xFE);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x01);
        }
    } else if ((memory->read(0xFF00) & 0x10) == 0) { //Bit 4
        if (keyboard->down) {
            memory->write(0xFF00, memory->read(0xFF00) & 0xF7);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x08);
        }
        if (keyboard->up) {
            memory->write(0xFF00, memory->read(0xFF00) & 0xFB);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x04);
        }
        if (keyboard->left) {
            memory->write(0xFF00, memory->read(0xFF00) & 0xFD);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x02);
        }
        if (keyboard->right) {
            memory->write(0xFF00, memory->read(0xFF00) & 0xFE);
        } else {
            memory->write(0xFF00, memory->read(0xFF00) | 0x01);
        }
    }
}
}
