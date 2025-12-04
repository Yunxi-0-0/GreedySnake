#include "mainwindow.h"
#include "page/GamePage.h"
#include "page/StartPage.h"
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
    settingPage = new SettingPage(this);
    rankingPage = new RankingPage(this);
    gamePage = new GamePage(this);
    middlePage = new MiddlePage(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(startPage);
    stackedWidget->addWidget(settingPage);
    stackedWidget->addWidget(rankingPage);
    stackedWidget->addWidget(gamePage);
    stackedWidget->addWidget(middlePage);

    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentWidget(startPage);
}

void MainWindow::initConnections(){
    connect(startPage, &StartPage::StartPageStart, this, [=](){
        stackedWidget->setCurrentWidget(middlePage);
        // gamePage->reset();
    });
    connect(startPage, &StartPage::StartPageSettings, this, [=](){
        stackedWidget->setCurrentWidget(settingPage);
    });
    connect(startPage, &StartPage::StartPageRanking, this, [=](){
        stackedWidget->setCurrentWidget(rankingPage);
    });
    connect(middlePage, &MiddlePage::startGame, this, [=](){
        stackedWidget->setCurrentWidget(gamePage);
    });
    connect(middlePage, &MiddlePage::exitGame, this, [=](){
        stackedWidget->setCurrentWidget(startPage);
    });
    connect(gamePage, &GamePage::exitGame, this, [this](){
        stackedWidget->setCurrentWidget(startPage);
    });
    connect(settingPage, &SettingPage::backButtonClicked, this, [=](){
        stackedWidget->setCurrentWidget(startPage);
    });
    connect(rankingPage, &RankingPage::backButtonClicked, this, [=](){
        stackedWidget->setCurrentWidget(startPage);
    });
    connect(startPage, &StartPage::StartPageExit, this, &QApplication::quit);
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