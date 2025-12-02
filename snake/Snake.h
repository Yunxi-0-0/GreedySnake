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
    enum  Direction { UP, DOWN, LEFT, RIGHT };
    void setDirection( Direction direction);
    Direction getDirection() const;
    QPoint getHead() const;
    QVector<QPoint> getBody() const;
    int getScore() const;
    int getSize() const;
    void move();

    void eat(Food* food);
    void grow();
    
private:
    QVector<QPoint> body;
    Direction direction = UP;
    QPoint head;
    int speed = 10;
    int size = 10;
    int score = 0;

    friend class Food;
signals:
    void scoreChanged(int score);

};
    