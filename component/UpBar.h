#pragma once
#include "qobject.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QTime>

class UpBar : public QWidget{
    Q_OBJECT
public:
    UpBar(QWidget *parent = nullptr);
private:
    QPushButton *homeBtn;
    QPushButton *stopBtn;
    QPushButton *startBtn;
    QLabel *titleLabel;
    QLabel *scoreLabel;
    QLabel *scoreLabel2;
    QLabel *scoreLabel3;
    QString Score = " Score: ";
    QLabel *timeLabel;
    QString Time = " Time: ";
    QTime *time;
    QString playerName ="Unnamed Snake";
    QString playerName2 ="Unnamed Snake";
    QString playerName3 ="Unnamed Snake";
    int score = 0;
    int score2 = 0;
    int score3 = 0;

    QHBoxLayout *layout;
    QVBoxLayout *playerLayout;
    void initUI();
    void initConnections();

public slots:
    void changeScore(int player, int score);
    void changePlayerName(int player, QString name);
    void changeLanguage(QString language);
    void addTime();

signals:
    void startGame();
    void stopGame();


public slots:
};