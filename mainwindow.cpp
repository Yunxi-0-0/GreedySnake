#include "mainwindow.h"
#include "page/GamePage.h"
#include "page/StartPage.h"
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QApplication>
#include "qurl.h"
#include "tools/Tools.h"
#include "tools/tools.h"
#include <QMediaDevices>
#include <QAudioDevice>
#include <QAudioSink>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(720, 600);
    initUI();
    initConnections();
    setupAudio();
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
    settingPage = new SettingPage(nullptr, this);
    rankingPage = new RankingPage(this);
    gamePage = new GamePage(this);
    difficultyPage = new DifficultyPage(this);
    middlePage = new MiddlePage(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(startPage);
    stackedWidget->addWidget(settingPage);
    stackedWidget->addWidget(rankingPage);
    stackedWidget->addWidget(gamePage);
    stackedWidget->addWidget(difficultyPage);
    stackedWidget->addWidget(middlePage);

    setCentralWidget(stackedWidget);

    stackedWidget->setCurrentWidget(startPage);
}

void MainWindow::initConnections(){
    //开始页面切换到难度界面
    connect(startPage, &StartPage::StartPageStart, this, [=](){
        // stackedWidget->setCurrentWidget(middlePage);
        stackedWidget->setCurrentWidget(difficultyPage);
        // gamePage->reset();
    });
    //难度界面切换到游戏界面
    connect(difficultyPage, &DifficultyPage::startGame, this, [=](){
        stackedWidget->setCurrentWidget(middlePage);
    });
    //难度界面切换到开始界面
    connect(difficultyPage, &DifficultyPage::backButtonClicked, this, [=](){
        stackedWidget->setCurrentWidget(startPage);
    });
    //难度界面选择难度
    connect(difficultyPage, &DifficultyPage::difficultySelected, gamePage, &GamePage::changeDifficulty);
    //开始页面切换到设置界面
    connect(startPage, &StartPage::StartPageSettings, this, [=](){
        stackedWidget->setCurrentWidget(settingPage);
    });
    //开始页面切换到排行榜界面
    connect(startPage, &StartPage::StartPageRanking, this, [=](){
        stackedWidget->setCurrentWidget(rankingPage);
    });
    //中间界面切换到游戏界面
    connect(middlePage, &MiddlePage::startGame, this, [=](){
        stackedWidget->setCurrentWidget(gamePage);
    });
    //中间界面切换到开始界面
    connect(middlePage, &MiddlePage::exitGame, this, [=](){
        stackedWidget->setCurrentWidget(startPage);
    });
    //游戏界面切换到开始界面
    connect(gamePage, &GamePage::exitGame, this, [this](){
        stackedWidget->setCurrentWidget(startPage);
    });
    //设置界面切换到开始界面
    connect(settingPage, &SettingPage::backButtonClicked, this, [=](){
        stackedWidget->setCurrentWidget(startPage);
    });
    //排行榜界面切换到开始界面
    connect(rankingPage, &RankingPage::backButtonClicked, this, [=](){
        stackedWidget->setCurrentWidget(startPage);
    });
    //开始页面退出程序
    connect(startPage, &StartPage::StartPageExit, this, &QApplication::quit);
    //中间界面切换玩家颜色
    connect(middlePage, &MiddlePage::changePlayerColour, gamePage, &GamePage::setPlayerColour);
    //中间界面切换玩家控制器
    connect(middlePage, &MiddlePage::changePlayerController, gamePage, &GamePage::setPlayerController);
    //中间界面切换玩家名字
    connect(middlePage, &MiddlePage::changePlayerName, gamePage, &GamePage::changePlayerName);
    //切换语言
    connect(settingPage, &SettingPage::languageChanged, this, &MainWindow::changeLanguage);
    //设置音量
    connect(settingPage, &SettingPage::volumeChanged, this, &MainWindow::changeVolume);

    connect(settingPage, &SettingPage::themeChanged, this, &MainWindow::applyTheme);

}

void MainWindow::applyTheme(QString theme){
    QString styleSheetPath = getstylesheetPath(theme + ".qss");
    QFile file(styleSheetPath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}

void MainWindow::setupAudio()
{
    // 创建音频播放器
    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.5);

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);

    mediaPlayer->setSource(QUrl::fromLocalFile(getMusicPath("background.mp3")));
    mediaPlayer->setLoops(QMediaPlayer::Infinite);
    mediaPlayer->play();
}

void MainWindow::changeLanguage(QString language){
    if(language == "zh"){
        this->setWindowTitle("贪吃蛇");
        startPage->changeLanguage(language);
        // rankingPage->changeLanguage(language);
        gamePage->changeLanguage(language);
        difficultyPage->changeLanguage(language);
        middlePage->changeLanguage(language);
    }else if(language == "en"){
        this->setWindowTitle("GreedySnake");
        startPage->changeLanguage(language);
        // rankingPage->changeLanguage(language);
        gamePage->changeLanguage(language);
        difficultyPage->changeLanguage(language);
        middlePage->changeLanguage(language);
    }
}

void MainWindow::changeVolume(double volume){
    audioOutput->setVolume(volume);
    gamePage->changeVolume(volume);
}