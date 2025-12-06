#include "mainwindow.h"
#include "page/GamePage.h"
#include "page/StartPage.h"
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QApplication>
#include "tools/Tools.h"

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

    QIcon icon(getIconPath("icon.ico"));
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

    connect(middlePage, &MiddlePage::changePlayerColour, gamePage, &GamePage::setPlayerColour);
    connect(middlePage, &MiddlePage::changePlayerController, gamePage, &GamePage::setPlayerController);
}

void MainWindow::applyTheme(QString theme){
    QString styleSheetPath = getstylesheetPath(theme + ".qss");
    QFile file(styleSheetPath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}