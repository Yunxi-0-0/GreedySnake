#pragma once
#include "qboxlayout.h"
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

    void initUI();
    void initConnections();

private slots:

signals:
    void StartPageStart();
    void StartPageSettings();
    void StartPageExit();
};
