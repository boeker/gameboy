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

 public slots:
    void refresh();
    void step();

 private:
    QString toHexString(int value);

 private:
    Ui::DebuggerWindow *ui;

    MainWindow *mainWindow;
    gameboy::Core *gameboyCore;
    EmuThread *emuThread;
};

#endif