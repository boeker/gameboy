#ifndef GUI_EMUTHREAD_H
#define GUI_EMUTHREAD_H

#include <QObject>
#include <QThread>
#include <QSize>
#include <atomic>

class Sound_Queue;

namespace gameboy {
class Core;
}

class ScreenWidget;

class EmuThread : public QThread {
    Q_OBJECT

 public:
    EmuThread(gameboy::Core *, ScreenWidget *);
    virtual ~EmuThread();
    void run();

    std::atomic<bool> stopped;
    std::atomic<bool> soundEnabled;
    std::atomic<bool> singleStep;

 private:
    gameboy::Core *gameboyCore;
    ScreenWidget *screenWidget;
    Sound_Queue *soundQueue;
};

#endif
