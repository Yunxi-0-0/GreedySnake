#pragma once
#include "qboxlayout.h"
#include "qobject.h"
#include "qpushbutton.h"
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>

class StartPage : public QWidget
{
    Q_OBJECT
public:
    StartPage(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QPushButton *startButton;
    QLabel *titleLabel;
    QPushButton *exitButton;
    QPushButton *settingsButton;
    QPushButton *rankingButton;

    void initUI();
    void initConnections();

public slots:
    void changeLanguage(QString language);
signals:
    void StartPageStart();
    void StartPageSettings();
    void StartPageRanking();
    void StartPageExit();
};
