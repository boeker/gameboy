#include "debuggerwindow.h"

#include "ui_debuggerwindow.h"
#include <QCheckbox>
#include "mainwindow.h"
#include "emuthread.h"
#include "gameboy/core.h"
#include "gameboy/cpuregisters.h"

DebuggerWindow::DebuggerWindow(QWidget *parent, gameboy::Core *core,
                               MainWindow *mainWindow, EmuThread *emuThread) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::DebuggerWindow),
    mainWindow(mainWindow),
    gameboyCore(core),
    emuThread(emuThread) {
        ui->setupUi(this);
}

DebuggerWindow::~DebuggerWindow() {
}

void DebuggerWindow::refresh() {
    ui->labelAFVal->setText(toHexString(gameboyCore->registers->getAF()));
    ui->labelBCVal->setText(toHexString(gameboyCore->registers->getBC()));
    ui->labelDEVal->setText(toHexString(gameboyCore->registers->getDE()));
    ui->labelHLVal->setText(toHexString(gameboyCore->registers->getHL()));
    ui->labelSPVal->setText(toHexString(gameboyCore->registers->getSP()));
    ui->labelPCVal->setText(toHexString(gameboyCore->registers->pc));

    ui->checkBoxZeroFlag->setChecked(gameboyCore->registers->getZeroFlag());
    ui->checkBoxSubFlag->setChecked(gameboyCore->registers->getSubFlag());
    ui->checkBoxHalfCarryFlag->setChecked(gameboyCore->registers->getHalfCarryFlag());
    ui->checkBoxCarryFlag->setChecked(gameboyCore->registers->getCarryFlag());
}

void DebuggerWindow::step() {
    mainWindow->pauseEmulation();

    emuThread->singleStep = true;
    mainWindow->continueEmulation();
    mainWindow->pauseEmulation();
    emuThread->singleStep = false;

    refresh();
}


QString DebuggerWindow::toHexString(int value) {
    return QString("%1").arg(value, 4, 16, QChar('0')).toUpper();
}