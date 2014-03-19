#ifndef GUI_DEBUGGERWINDOW_H
#define GUI_DEBUGGERWINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
class DebuggerWindow;
}

namespace gameboy {
class Core;
}

class MainWindow;
class EmuThread;

class DebuggerWindow : public QDialog {
    Q_OBJECT

 public:
    explicit DebuggerWindow(QWidget *parent, gameboy::Core *core,
                            MainWindow *mainWindow, EmuThread *emuThread);
    ~DebuggerWindow();
    bool controlsOverridden();

 public slots:
    void loadMemory();
    void jumpToPC();
    void refresh();
    void step();
    void clickedUp(bool status);
    void clickedDown(bool status);
    void clickedLeft(bool status);
    void clickedRight(bool status);
    void clickedA(bool status);
    void clickedB(bool status);
    void clickedStart(bool status);
    void clickedSelect(bool status);

 private:
    QString toDoubleHexString(int value);
    QString toByteHexString(int value);

 private:
    Ui::DebuggerWindow *ui;

    MainWindow *mainWindow;
    gameboy::Core *gameboyCore;
    EmuThread *emuThread;
};

#endif