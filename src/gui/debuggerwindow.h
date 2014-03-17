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

class DebuggerWindow : public QDialog {
    Q_OBJECT

 public:
    explicit DebuggerWindow(QWidget *parent, gameboy::Core *core);
    ~DebuggerWindow();

 public slots:
    void refresh();

 private:
    QString toHexString(int value);

 private:
    Ui::DebuggerWindow *ui;
    gameboy::Core *gameboyCore;
};

#endif