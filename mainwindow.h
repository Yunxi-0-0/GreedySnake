#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once


#include <QMainWindow>
#include "page/StartPage.h"
#include "page/GamePage.h"
#include <QStackedWidget>
#include <QFile>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    StartPage* startPage;
    GamePage* gamePage;

    QStackedWidget* stackedWidget;

    void initUI();
    void initConnections();
    void applyTheme(QString theme);

};
#endif // MAINWINDOW_H
