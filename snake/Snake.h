#pragma once

#include <QObject>
#include <QVector>
#include <QPoint>
#include "../food/Food.h"
#include "qtmetamacros.h"

class Snake : public QObject {
    Q_OBJECT
public:
    Snake();
    Snake(int size, int speed, int FPS);
    enum  Direction { UP, DOWN, LEFT, RIGHT };
    void setDirection( Direction direction);
    Direction getDirection() const;
    QPoint getHead() const;
    QVector<QPoint> getBody() const;
    int getScore() const;
    int getSize() const;
    int getSpeed() const;
    void setSpeed(int speed);
    int getTotalLength() const;
    void move();

    void eat(Food* food);
    void grow();
    void reGenerate();

    
private:
    QVector<QPoint> body;
    Direction direction = UP;
    QPoint head;
    int speed = 100;
    int size = 10;
    int score = 0;
    int stepLength = 1;
    int FPS = 100;

    void generate();

    friend class Food;
signals:
    void scoreChanged(int score);

};
    