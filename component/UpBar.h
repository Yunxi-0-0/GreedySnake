#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>

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
    QLabel *timeLabel;

    QHBoxLayout *layout;
    void initUI();
    void initConnections();

public slots:
    void changeScore(int score);

signals:
    void startGame();
    void stopGame();


public slots:
};