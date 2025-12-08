#pragma once

#include <QWidget>
#include <QPainter>
#include "../snake/Snake.h"
#include <QTimer>
#include <qaction.h>
#include <qmediaplayer.h>
#include "../food/Food.h"
#include "GameOverDialog.h"
#include "qtimer.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "../landmine/Landmine.h"


class GameArea : public QWidget
{
    Q_OBJECT
public:
    explicit GameArea(QWidget *parent = nullptr);
    void start();
    void stop();
    bool isRunning() const;
    int getSnakeNumber() const;
    int getSnakeScore(Snake *snake);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Snake *snake;
    Snake *snake2;
    Snake *snake3;
    
    QTimer *timer;
    QTimer *foodTimer;
    QTimer *landmineTimer;
    QTimer *Timer;
    int FPS = 100;
    bool is_Running = false;
    bool is_Food_Generated = false;
    Food *food;
    QVector<Food *> foods = {};
    QVector<Landmine *> landmines = {};
    int foodLimit = 10;
    int landmineLimit = 10;
    int speed = 100;
    int difficulty = 2;

    QMediaPlayer *diedMediaPlayer;
    QAudioOutput *diedAudioOutput;
    QMediaPlayer *eatMediaPlayer;
    QAudioOutput *eatAudioOutput;

    void generateFood();
    void generateFood(Food *food);
    void addFood();
    void addLandmine();
    void removeFood(Food *food);
    void removeLandmine(Landmine *landmine);
    void totalCheck();
    bool checkEatFood(Snake *snake, Food *food);
    void checkEatFood(Snake *snake, QVector<Food *> foods);
    bool checkEatLandmine(Snake *snake, Landmine *landmine);
    void checkEatLandmine(Snake *snake, QVector<Landmine *> landmines);
    bool checkCollision(Snake *snake);
    bool checkCollisionBetweenSnakes(Snake *snake1, Snake *snake2);
    void printSnake(QPainter &painter, Snake *snake);
    void printFood(QPainter &painter, Food *food);
    void printLandmine(QPainter &painter, Landmine *landmine);
    void controlSnake(QKeyEvent *event, Snake *snake, Snake::Control control);
    void control(QKeyEvent *event);
    QVector<QPoint> getObstacles() const;
    void backEnd();

    QString getPlayerName(int player) const;
public slots:
    void restart();
    void exitGame();
    void setSnakeColour(int player, Snake::Colour colour);
    void setSnakeController(int player, Snake::Controller controller);
    void setSnakeName(int player, QString name);
    void snakeDied(Snake *snake);
    void setDifficulty(int difficulty);
    void playDiedSound();
    void changeVolume(double volume);

signals:
    void scoreChanged(int player, int score);
    void gameOver();
    void snakeCollided(Snake *snake);
    void backEndSnakeScore(Snake *snake);
    void eat(Food *food);
    void addTime();
};