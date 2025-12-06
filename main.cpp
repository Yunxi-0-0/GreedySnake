#include "mainwindow.h"
#include "qdir.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QMessageBox>
#include "qmessagebox.h"
#include "tools/Tools.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
