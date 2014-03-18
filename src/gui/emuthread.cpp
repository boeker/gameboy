#include "emuthread.h"

#include <QDebug>
#include "gameboy/core.h"
#include "screenwidget.h"

EmuThread::EmuThread(gameboy::Core *core,
                    ScreenWidget *widget) :
    QThread(0),
    stopped(false),
    singleStep(false),
    gameboyCore(core),
    screenWidget(widget) {
}

void EmuThread::run() {
    if (singleStep) {
        gameboyCore->emulateCycle();
        if (gameboyCore->drawFlagSet()) {
            screenWidget->updateGL();
        }
    } else {
        while (!stopped) {
            gameboyCore->emulateUntilVBlank();

            if (screenWidget->resizeNeeded) {
                screenWidget->resizePub(screenWidget->newWidth, screenWidget->newHeight);
                screenWidget->resizeNeeded = false;
            }

            screenWidget->updateGL();
        }
    }
}
