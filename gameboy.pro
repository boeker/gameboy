QT += core gui widgets opengl
TEMPLATE = app
TARGET = gameboy
INCLUDEPATH += src
CONFIG += c++11 console

HEADERS += src/gui/mainwindow.h \
           src/gui/screenwidget.h \
           src/gui/emuthread.h \
           src/gui/debuggerwindow.h \
           src/gameboy/core.h \
           src/gameboy/cpuregisters.h \
           src/gameboy/keyboard.h \
           src/gameboy/memory.h \
           src/gameboy/screen.h \
           src/gameboy/timer.h \
           src/gameboy/mbc/memorybankcontroller.h \
           src/gameboy/mbc/romonly.h \
           src/gameboy/mbc/mbc1.h \
           src/util/color.h
SOURCES += src/main.cpp \
           src/gui/mainwindow.cpp \
           src/gui/screenwidget.cpp \
           src/gui/emuthread.cpp \
           src/gui/debuggerwindow.cpp \
           src/gameboy/core.cpp \
           src/gameboy/core_opcodes.cpp \
           src/gameboy/core_opcodetables.cpp \
           src/gameboy/cpuregisters.cpp \
           src/gameboy/keyboard.cpp \
           src/gameboy/memory.cpp \
           src/gameboy/screen.cpp \
           src/gameboy/timer.cpp \
           src/gameboy/mbc/romonly.cpp \
           src/gameboy/mbc/mbc1.cpp \
           src/util/color.cpp
FORMS += src/gui/mainwindow.ui \
         src/gui/debuggerwindow.ui
