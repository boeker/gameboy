#include "debuggerwindow.h"

#include "ui_debuggerwindow.h"
#include <QCheckbox>
#include <QPalette>
#include "mainwindow.h"
#include "emuthread.h"
#include "gameboy/core.h"
#include "gameboy/memory.h"
#include "gameboy/cpuregisters.h"
#include "gameboy/keyboard.h"

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

bool DebuggerWindow::controlsOverridden() {
    return ui->groupBoxControls->isChecked();
}

void DebuggerWindow::loadMemory() {
    ui->listWidget->clear();

    for (int i = 0; i <= 0xFFFF; ++i) {
        ui->listWidget->addItem(toDoubleHexString(i) + ":  " + toByteHexString(gameboyCore->memory->read(i)));
    }
}

void DebuggerWindow::jumpToPC() {
    if (ui->listWidget->count() > 0) {
        ui->listWidget->setCurrentRow(0);
        ui->listWidget->setCurrentRow(gameboyCore->registers->pc);
    }
}

void DebuggerWindow::refresh() {
    ui->lineEditAF->setText(toDoubleHexString(gameboyCore->registers->getAF()));
    ui->lineEditBC->setText(toDoubleHexString(gameboyCore->registers->getBC()));
    ui->lineEditDE->setText(toDoubleHexString(gameboyCore->registers->getDE()));
    ui->lineEditHL->setText(toDoubleHexString(gameboyCore->registers->getHL()));
    ui->lineEditSP->setText(toDoubleHexString(gameboyCore->registers->getSP()));
    ui->lineEditPC->setText(toDoubleHexString(gameboyCore->registers->pc));

    ui->checkBoxZeroFlag->setChecked(gameboyCore->registers->getZeroFlag());
    ui->checkBoxSubFlag->setChecked(gameboyCore->registers->getSubFlag());
    ui->checkBoxHalfCarryFlag->setChecked(gameboyCore->registers->getHalfCarryFlag());
    ui->checkBoxCarryFlag->setChecked(gameboyCore->registers->getCarryFlag());
    ui->checkBoxIME->setChecked(gameboyCore->registers->getIME());
}

void DebuggerWindow::step() {
    mainWindow->pauseEmulation();

    emuThread->singleStep = true;
    mainWindow->continueEmulation();
    mainWindow->pauseEmulation();
    emuThread->singleStep = false;

    refresh();
    jumpToPC();
}

void DebuggerWindow::clickedUp(bool status) {
    gameboyCore->getKeyboard()->up = status;
}

void DebuggerWindow::clickedDown(bool status) {
    gameboyCore->getKeyboard()->down = status;
}

void DebuggerWindow::clickedLeft(bool status) {
    gameboyCore->getKeyboard()->left = status;
}

void DebuggerWindow::clickedRight(bool status) {
    gameboyCore->getKeyboard()->right = status;
}

void DebuggerWindow::clickedA(bool status) {
    gameboyCore->getKeyboard()->a = status;
}

void DebuggerWindow::clickedB(bool status) {
    gameboyCore->getKeyboard()->b = status;
}

void DebuggerWindow::clickedStart(bool status) {
    gameboyCore->getKeyboard()->start = status;
}

void DebuggerWindow::clickedSelect(bool status) {
    gameboyCore->getKeyboard()->select = status;
}


QString DebuggerWindow::toDoubleHexString(int value) {
    return QString("%1").arg(value, 4, 16, QChar('0')).toUpper();
}

QString DebuggerWindow::toByteHexString(int value) {
    return QString("%1").arg(value, 2, 16, QChar('0')).toUpper();
}