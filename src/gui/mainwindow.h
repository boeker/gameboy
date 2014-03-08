#ifndef GUI_MAINWINDOW_H
#define GUI_MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

namespace gameboy {
class Core;
class Keyboard;
}

class ScreenWidget;
class EmuThread;

class MainWindow : public QWidget {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

 private:
    Ui::MainWindow *ui;
    ScreenWidget *screenWidget;

    gameboy::Core *gameboyCore;
    gameboy::Keyboard *keyboard;
    EmuThread *emuThread;
};

#endif
