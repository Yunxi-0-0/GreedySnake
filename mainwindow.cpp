#include "mainwindow.h"
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(720, 600);
    initUI();
    initConnections();
    applyTheme("light");
    
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI(){
    this->setWindowTitle("Greedy Snake");

    QDir appDir(QCoreApplication::applicationDirPath());
    QString iconDir = QDir(appDir.filePath("..")).filePath("icon.ico");
    QIcon icon(iconDir);
    this->setWindowIcon(icon);

    startPage = new StartPage(this);
    gamePage = new GamePage(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(startPage);
    stackedWidget->addWidget(gamePage);
    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentWidget(startPage);
}

void MainWindow::initConnections(){
    connect(startPage, &StartPage::StartPageStart, this, [=](){
        stackedWidget->setCurrentWidget(gamePage);
    });
}

void MainWindow::applyTheme(QString theme){
    // 计算可移植的 styles 路径：exe 在 build 目录，styles 在项目根的 styles/ 下
    QDir appDir(QCoreApplication::applicationDirPath());
    // 假设可执行文件位于项目的 build 子目录，styles 在上一级目录的 styles 文件夹
    QString stylesDir = QDir(appDir.filePath("..")).filePath("styles");
    QString fileName = (theme == "dark") ? "dark.qss" : "light.qss";
    QString path = QDir(stylesDir).filePath(fileName);
    QFile file(path);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}