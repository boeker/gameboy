#ifndef GUI_EMUTHREAD_H
#define GUI_EMUTHREAD_H

#include <QObject>
#include <QThread>

namespace gameboy {
class Core;
}

class ScreenWidget;

class EmuThread : public QThread {
    Q_OBJECT

 public:
    EmuThread(gameboy::Core *, ScreenWidget *, QObject *);
    void run();

 private:
    gameboy::Core *gbCore;
    ScreenWidget *screenWidget;
};

#endif
