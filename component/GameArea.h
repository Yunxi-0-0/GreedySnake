#pragma once

#include <QWidget>
#include <QPainter>
#include "../snake/Snake.h"
#include <QTimer>
#include "../food/Food.h"
#include "GameOverDialog.h"


class GameArea : public QWidget
{
    Q_OBJECT
public:
    explicit GameArea(QWidget *parent = nullptr);
    void start();
    void stop();
    bool isRunning() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Snake *snake;
    QTimer *timer;
    int FPS = 100;
    bool is_Running = false;
    bool is_Food_Generated = false;
    Food *food;

    void generateFood();
    bool checkEatFood(Snake *snake, Food *food);
    bool checkCollision(Snake *snake);

public slots:
    void restart();
    void exitGame();

signals:
    void scoreChanged(int score);
    void gameOver();

};