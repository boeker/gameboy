QT += core gui widgets opengl
TEMPLATE = app
TARGET = gameboy
INCLUDEPATH += src
CONFIG += c++11 console debug
#DEFINES += QT_NO_DEBUG_OUTPUT

LIBS += -lSDL2

FORMS += src/gui/mainwindow.ui \
         src/gui/debuggerwindow.ui

HEADERS += src/gui/mainwindow.h \
           src/gui/screenwidget.h \
           src/gui/emuthread.h \
           src/gui/debuggerwindow.h \
           src/gameboy/audio.h \
           src/gameboy/core.h \
           src/gameboy/cpuregisters.h \
           src/gameboy/keyboard.h \
           src/gameboy/memory.h \
           src/gameboy/screen.h \
           src/gameboy/timer.h \
           src/gameboy/mbc/memorybankcontroller.h \
           src/gameboy/mbc/romonly.h \
           src/gameboy/mbc/mbc1.h \
           src/gameboy/mbc/mbc1ram.h \
           src/gameboy/mbc/mbc1rambatt.h \
           src/gameboy/mbc/mbc2.h \
           src/gameboy/mbc/mbc2batt.h \
           src/gameboy/mbc/mbc3.h \
           src/gameboy/mbc/mbc3ram.h \
           src/gameboy/mbc/mbc3rambatt.h \
           src/gameboy/mbc/mbc3tim.h \
           src/gameboy/mbc/mbc3timrambatt.h \
           src/gameboy/mbc/mbc5.h \
           src/gameboy/mbc/mbc5ram.h \
           src/gameboy/mbc/mbc5rambatt.h \
           src/util/color.h
           src/exceptions/breakpoint.h

SOURCES += src/main.cpp \
           src/gui/mainwindow.cpp \
           src/gui/screenwidget.cpp \
           src/gui/emuthread.cpp \
           src/gui/debuggerwindow.cpp \
           src/gameboy/audio.cpp \
           src/gameboy/core.cpp \
           src/gameboy/core_opcodes.cpp \
           src/gameboy/core_opcodetables.cpp \
           src/gameboy/core_timings.cpp \
           src/gameboy/cpuregisters.cpp \
           src/gameboy/keyboard.cpp \
           src/gameboy/memory.cpp \
           src/gameboy/screen.cpp \
           src/gameboy/timer.cpp \
           src/gameboy/mbc/memorybankcontroller.cpp \
           src/gameboy/mbc/romonly.cpp \
           src/gameboy/mbc/mbc1.cpp \
           src/gameboy/mbc/mbc1ram.cpp \
           src/gameboy/mbc/mbc1rambatt.cpp \
           src/gameboy/mbc/mbc2.cpp \
           src/gameboy/mbc/mbc2batt.cpp \
           src/gameboy/mbc/mbc3.cpp \
           src/gameboy/mbc/mbc3ram.cpp \
           src/gameboy/mbc/mbc3rambatt.cpp \
           src/gameboy/mbc/mbc3tim.cpp \
           src/gameboy/mbc/mbc3timrambatt.cpp \
           src/gameboy/mbc/mbc5.cpp \
           src/gameboy/mbc/mbc5ram.cpp \
           src/gameboy/mbc/mbc5rambatt.cpp \
           src/util/color.cpp

#blarrg's sound lib
HEADERS += src/gameboy/apu/blargg_common.h \
           src/gameboy/apu/blargg_config.h \
           src/gameboy/apu/blargg_source.h \
           src/gameboy/apu/Blip_Buffer.h \
           src/gameboy/apu/Blip_Synth.h \
           src/gameboy/apu/Effects_Buffer.h \
           src/gameboy/apu/Gb_Apu.h \
           src/gameboy/apu/Gb_Oscs.h \
           src/gameboy/apu/Multi_Buffer.h \
           src/gameboy/apu/Sound_Queue.h

SOURCES += src/gameboy/apu/Blip_Buffer.cpp \
           src/gameboy/apu/Effects_Buffer.cpp \
           src/gameboy/apu/Gb_Apu.cpp \
           src/gameboy/apu/Gb_Apu_State.cpp \
           src/gameboy/apu/Gb_Oscs.cpp \
           src/gameboy/apu/Multi_Buffer.cpp \
           src/gameboy/apu/Sound_Queue.cpp
