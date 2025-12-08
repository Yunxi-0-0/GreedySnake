#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "page/MiddlePage.h"
#include "page/RankingPage.h"
#pragma once


#include <QMainWindow>
#include "page/StartPage.h"
#include "page/GamePage.h"
#include "page/MiddlePage.h"
#include "page/SettingPage.h"
#include "page/RankingPage.h"
#include "page/Difficultypage.h"
#include <QStackedWidget>
#include <QFile>
#include <QMediaPlayer>
#include <QAudio>
#include <QAudioOutput>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    StartPage* startPage;
    GamePage* gamePage;
    DifficultyPage* difficultyPage;
    SettingPage* settingPage;
    RankingPage* rankingPage;
    MiddlePage* middlePage;

    QStackedWidget* stackedWidget;

    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;
    int FPS = 100;

    void initUI();
    void initConnections();
    void applyTheme(QString theme);
    void setupAudio();
public slots:
    void changeLanguage(QString language);
    void changeVolume(double volume);

};
#endif // MAINWINDOW_H
