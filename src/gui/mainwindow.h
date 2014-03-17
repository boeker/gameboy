#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <QMainWindow>

class QActionGroup;

namespace Ui {
class MainWindow;
}

namespace gameboy {
class Core;
class Keyboard;
}

class ScreenWidget;
class EmuThread;

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setScaling(int scaling);

 public slots:
    void continueEmulation();
    void pauseEmulation();
    void loadROM();
    void scale1x();
    void scale2x();
    void scale4x();
    void scale6x();

 protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

 private:
    Ui::MainWindow *ui;
    ScreenWidget *screenWidget;

    gameboy::Core *gameboyCore;
    gameboy::Keyboard *keyboard;
    EmuThread *emuThread;

    QActionGroup *videoScalingGroup;
};

#endif
