#include "emuthread.h"

#include "gameboy/core.h"
#include "screenwidget.h"

EmuThread::EmuThread(gameboy::Core *core,
                    ScreenWidget *widget, QObject *parent) :
    QThread(parent),
    gbCore(core),
    screenWidget(widget) {
}

void EmuThread::run() {
    while (true) {
        gbCore->emulateUntilVBlank();
        screenWidget->updateGL();
    }
}
