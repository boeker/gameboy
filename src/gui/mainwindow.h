#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <QMainWindow>

class QActionGroup;
class DebuggerWindow;

namespace Ui {
class MainWindow;
}

namespace gameboy {
class Core;
class Keyboard;
}

class ScreenWidget;
class EmuThread;
class QDropEvent;
class QDragEnterEvent;

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setScaling(int scaling);
    void loadROM(const QString &file);

 public slots:
    void debugger();
    void continueEmulation();
    void pauseEmulation();
    void loadROM();
    void reset();
    void scale1x();
    void scale2x();
    void scale4x();
    void scale6x();

 protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void dragEnterEvent(QDragEnterEvent *ev);
    void dropEvent(QDropEvent *ev);

 private:
    Ui::MainWindow *ui;
    ScreenWidget *screenWidget;

    gameboy::Core *gameboyCore;
    gameboy::Keyboard *keyboard;
    EmuThread *emuThread;

    QActionGroup *videoScalingGroup;

    DebuggerWindow *debuggerWindow;

    QString currentROM;
};

#endif
