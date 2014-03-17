#ifndef GUI_EMUTHREAD_H
#define GUI_EMUTHREAD_H

#include <QObject>
#include <QThread>
#include <QSize>

namespace gameboy {
class Core;
}

class ScreenWidget;

class EmuThread : public QThread {
    Q_OBJECT

 public:
    EmuThread(gameboy::Core *, ScreenWidget *);
    void run();

    volatile bool stopped;

 private:
    gameboy::Core *gbCore;
    ScreenWidget *screenWidget;
};

#endif
