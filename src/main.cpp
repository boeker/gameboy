// Copyright (c) 2014 Jan Böker
// MIT License

#include <QApplication>
#include "gui/mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    return app.exec();
}
