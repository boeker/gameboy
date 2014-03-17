#include "emuthread.h"

#include "gameboy/core.h"
#include "screenwidget.h"

EmuThread::EmuThread(gameboy::Core *core,
                    ScreenWidget *widget) :
    QThread(0),
    stopped(false),
    gbCore(core),
    screenWidget(widget) {
}

void EmuThread::run() {
    while (!stopped) {
        gbCore->emulateUntilVBlank();

        if (screenWidget->resizeNeeded) {
            screenWidget->resizePub(screenWidget->newWidth, screenWidget->newHeight);
            screenWidget->resizeNeeded = false;
        }

        screenWidget->updateGL();
    }
}
