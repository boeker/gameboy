#include "mainwindow.h"

#include <QActionGroup>
#include <QDebug>
#include <QDropEvent>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMimeData>
#include <QString>
#include <QStringList>
#include "ui_mainwindow.h"
#include "debuggerwindow.h"
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

    gameboyCore = new gameboy::Core;

    keyboard = gameboyCore->getKeyboard();

    screenWidget = new ScreenWidget(this);
    screenWidget->setFramebuffer(gameboyCore->getFramebuffer());
    setCentralWidget(screenWidget);

    setScaling(4);

    emuThread = new EmuThread(gameboyCore, screenWidget);
    screenWidget->doneCurrent();
    screenWidget->context()->moveToThread(emuThread);

    debuggerWindow = new DebuggerWindow(this, gameboyCore, this, emuThread);

    QStringList args = QCoreApplication::arguments();
    if (args.size() > 1) {
        loadROM(args.at(1));
    }
}

MainWindow::~MainWindow() {
    pauseEmulation();
    delete emuThread;
    delete gameboyCore;

    delete ui;
}

void MainWindow::setScaling(int scaling) {
    screenWidget->resize(160*scaling, 144*scaling);
    resize(160*scaling, 144*scaling + ui->menubar->height());
}

void MainWindow::debugger() {
    pauseEmulation();

    if (!debuggerWindow->isVisible()) {
        debuggerWindow->show();
    }
    
    debuggerWindow->refresh();   
}

void MainWindow::continueEmulation() {
    if (!emuThread->isRunning()) {
        emuThread->stopped = false;
        emuThread->start();
    }
    ui->actionContinue->setEnabled(false);
    ui->actionPause->setEnabled(true);
}

void MainWindow::pauseEmulation() {
    if (emuThread->isRunning()) {
        emuThread->stopped = true;
        emuThread->wait();
    }
    ui->actionContinue->setEnabled(true);
    ui->actionPause->setEnabled(false);
}

void MainWindow::loadROM() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open ROM", "", "Gameboy ROMs (*.gb)");

    if (!fileName.isNull()) {
        loadROM(fileName);
    }
}

void MainWindow::loadROM(const QString &file) {
    pauseEmulation();

    gameboyCore->reset();
    gameboyCore->loadROM(file.toStdString());

    //continueEmulation();
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
    if (!debuggerWindow->controlsOverridden()) {
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
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!debuggerWindow->controlsOverridden()) {
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
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = static_cast<QDropEvent*>(event)->mimeData();

    if (mimeData->hasUrls()) {
        loadROM(mimeData->urls().at(0).toLocalFile());
    }
}