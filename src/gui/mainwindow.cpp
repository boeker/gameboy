#include "mainwindow.h"

#include <QActionGroup>
#include <QKeyEvent>
#include "ui_mainwindow.h"
#include "screenwidget.h"
#include "emuthread.h"
#include "gameboy/core.h"
#include "gameboy/keyboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    videoScalingGroup(new QActionGroup(this)) {
    ui->setupUi(this);

    videoScalingGroup->addAction(ui->action1x);
    videoScalingGroup->addAction(ui->action2x);
    videoScalingGroup->addAction(ui->action4x);
    videoScalingGroup->addAction(ui->action6x);

    gameboyCore = new gameboy::Core("tetris.gb");
    keyboard = gameboyCore->getKeyboard();

    screenWidget = new ScreenWidget(this);
    screenWidget->setFramebuffer(gameboyCore->getFramebuffer());
    setCentralWidget(screenWidget);

    setScaling(4);

    emuThread = new EmuThread(gameboyCore, screenWidget, 0);
    screenWidget->doneCurrent();
    screenWidget->context()->moveToThread(emuThread);
    emuThread->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadROM() {
    
}

void MainWindow::setScaling(int scaling) {
    screenWidget->resize(160*scaling, 144*scaling);
    resize(160*scaling, 144*scaling + ui->menubar->height());
}

void MainWindow::scale1x() {
    setScaling(1);
}

void MainWindow::scale2x() {
    setScaling(2);
}

void MainWindow::scale4x() {
    setScaling(4);
}

void MainWindow::scale6x() {
    setScaling(6);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        keyboard->up = true;
    break;
    case Qt::Key_Down:
        keyboard->down = true;
    break;
    case Qt::Key_Left:
        keyboard->left = true;
    break;
    case Qt::Key_Right:
        keyboard->right = true;
    break;
    case Qt::Key_C:
        keyboard->select = true;
    break;
    case Qt::Key_V:
        keyboard->start = true;
    break;
    case Qt::Key_F:
        keyboard->a = true;
    break;
    case Qt::Key_D:
        keyboard->b = true;
    break;
    default: //To make the compiler STFU
    break;
   } 
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            keyboard->up = false;
        break;
        case Qt::Key_Down:
            keyboard->down = false;
        break;
        case Qt::Key_Left:
            keyboard->left = false;
        break;
        case Qt::Key_Right:
            keyboard->right = false;
        break;
        case Qt::Key_C:
            keyboard->select = false;
        break;
        case Qt::Key_V:
            keyboard->start = false;
        break;
        case Qt::Key_F:
            keyboard->a = false;
        break;
        case Qt::Key_D:
            keyboard->b = false;
        break;
        default: //To make the compiler STFU
        break;
    }
}

