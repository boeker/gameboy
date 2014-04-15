// Copyright (c) 2014 Jan Böker
// MIT License

#include "emuthread.h"

#include <QDebug>
#include "gameboy/core.h"
#include "exceptions/breakpoint.h"
#include "screenwidget.h"

#include "gameboy/audio.h"
#include "gameboy/apu/Sound_Queue.h"

EmuThread::EmuThread(gameboy::Core *core,
                    ScreenWidget *widget) :
    QThread(0),
    stopped(false),
    soundEnabled(true),
    singleStep(false),
    gameboyCore(core),
    screenWidget(widget),
    soundQueue(new Sound_Queue) {
    soundQueue->start(gameboyCore->audio->sampleRate, 2);
}

EmuThread::~EmuThread() {
    delete soundQueue;
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

                if (soundEnabled && gameboyCore->audio->getPlayFlag()) {
                    soundQueue->write(gameboyCore->audio->getSampleBuffer(), gameboyCore->audio->getSampleCount());
                }
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
