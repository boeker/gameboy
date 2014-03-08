QT += core gui widgets opengl
TEMPLATE = app
TARGET = gameboy
INCLUDEPATH += src
CONFIG += c++11

HEADERS += src/gui/mainwindow.h \
           src/gui/screenwidget.h \
           src/gui/emuthread.h \
           src/gameboy/core.h \
           src/gameboy/cpuregisters.h \
           src/gameboy/keyboard.h \
           src/gameboy/memory.h \
           src/gameboy/screen.h \
           src/util/color.h
SOURCES += src/main.cpp \
           src/gui/mainwindow.cpp \
           src/gui/screenwidget.cpp \
           src/gui/emuthread.cpp \
           src/gameboy/core.cpp \
           src/gameboy/cpuregisters.cpp \
           src/gameboy/keyboard.cpp \
           src/gameboy/memory.cpp \
           src/gameboy/screen.cpp \
           src/util/color.cpp
FORMS += src/gui/mainwindow.ui
