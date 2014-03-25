#include "emuthread.h"

#include <QDebug>
#include "gameboy/core.h"
#include "exceptions/breakpoint.h"
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
            try {
                gameboyCore->emulateUntilVBlank();

                if (screenWidget->resizeNeeded) {
                    screenWidget->resizePub(screenWidget->newWidth, screenWidget->newHeight);
                    screenWidget->resizeNeeded = false;
                }

                screenWidget->updateGL();
            } catch (exceptions::Breakpoint& bp) {
                qDebug() << "Breakpoint";
                return;
            }
        }
    }
}
