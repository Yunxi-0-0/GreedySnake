#pragma once

#include <QObject>
#include <QVector>
#include <QPoint>
#include "../food/Food.h"
#include "qcontainerfwd.h"
#include "qpoint.h"
#include "qtmetamacros.h"
#include <QMap>
#include <QSet>

class Snake : public QObject {
    Q_OBJECT
public:
    Snake();
    Snake(int size, int speed, int FPS);
    Snake(int size, int speed, int FPS,bool isEnabled, bool isAi, QPoint initialPosition);
    enum  Direction { UP, DOWN, LEFT, RIGHT };
    enum  Colour { RED, GREEN, BLUE, YELLOW, BLACK, MAGENTA };
    enum  Control { WASD, IJKL , COMMON};
    enum  Controller { ENABLED, DISABLED ,AI};
    void setDirection( Direction direction);
    Direction getDirection() const;
    QPoint getHead() const;
    QVector<QPoint> getBody() const;
    int getScore() const;
    int getSize() const;
    int getSpeed() const;
    void setSpeed(int speed);
    int getFPS() const;
    void setFPS(int FPS);
    int getStepLength() const;
    int getTotalLength() const;
    Colour getColour() const;
    void setColour(Colour colour);
    bool IsAi() const;
    void setAi(bool isAi);
    bool IsEnabled() const;
    void setEnabled(bool enabled);
    bool IsAlive() const;
    void setAlive(bool isAlive);
    void setController(Controller controller);
    Controller getController() const;
    QString getName() const;
    void setName(QString name);
    void setDifficulty(int difficulty);

    void move();
    void eat(Food* food);
    void grow();
    void reGenerate();
    void routePlanning(QVector<QPoint> obstacles, QVector<Food*> foods);
    
private:
    QVector<QPoint> body;
    Direction direction = UP;
    Colour colour = GREEN;
    Control control = COMMON;
    Controller controller = DISABLED;
    QPoint head;
    int difficulty = 2;
    int speed = 100;
    int size = 10;
    int score = 0;
    int stepLength = 1;
    int FPS = 100;
    bool isAi = false;
    bool isEnabled = false;
    bool isAlive = false;
    QString name;
    QPoint initialPosition;
    QVector<QPoint> route;

    void generate();
    void generate(QPoint initialPosition);

    friend class Food;
signals:
    void scoreChanged(int score);
};
    