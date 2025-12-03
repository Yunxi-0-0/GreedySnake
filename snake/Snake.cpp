#include "snake.h"
#include "qgraphicsitem.h"
#include "qpoint.h"
#include "qtmetamacros.h"

Snake::Snake()
{
    generate();

}

Snake::Snake(int size, int speed, int FPS){
    this->size = size;
    this->speed = speed;
    this->FPS = FPS;
    this->stepLength = speed / FPS;
    this->score = 0;
    generate();
}

QVector<QPoint> Snake::getBody() const
{
    return body;
}

QPoint Snake::getHead() const
{
    return head;
}



int Snake::getScore() const
{
    return score;
}

int Snake::getSize() const
{
    return size;
}

void Snake::move(){
    switch (direction) {
    case UP:
        body.insert(0, {head.x(), head.y() - stepLength});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case DOWN:
        body.insert(0, {head.x(), head.y() + stepLength});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case LEFT:
        body.insert(0, {head.x() - stepLength, head.y()});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case RIGHT:
        body.insert(0, {head.x() + stepLength, head.y()});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    }
}

void Snake::setDirection(Direction direction)
{
    this->direction = direction;
}

Snake::Direction Snake::getDirection() const
{
    return direction;
}

void Snake::eat(Food* food)
{
        score += 10;
        emit scoreChanged(score);
        grow();
}

void Snake::grow()
{
    switch (direction) {
    case UP:
        for(int i = 0; i < 10 / stepLength; i++){
            body.append(body.last() + QPoint(0, stepLength));
        }
        break;
    case DOWN:
        for(int i = 0; i < 10 / stepLength; i++){
            body.append(body.last() + QPoint(0, -stepLength));
        }
        break;
    case RIGHT:
        for(int i = 0; i < 10 / stepLength; i++){
            body.append(body.last() + QPoint(-stepLength, 0));
        }
        break;
    case LEFT:
        for(int i = 0; i < 10 / stepLength; i++){
            body.append(body.last() + QPoint(stepLength, 0));
        }
        break;
    }
    
}

void Snake::generate(){

    direction = UP;
    head = QPoint(360, 240);
    body.append(head);
    // 将初始身体放在头部的后方，避免第一次移动时重叠
    for(int i = 1; i < 50 / stepLength; i++){
        body.append(body.last() + QPoint(0, +stepLength));
    }
    
}

void Snake::reGenerate(){
    body.clear();
    score = 0;
    emit scoreChanged(score);
    generate();
}

int Snake::getSpeed() const{
    return speed;
}

void Snake::setSpeed(int speed){
    this->speed = speed;
    this->stepLength = speed / FPS;
}

int Snake::getTotalLength() const{
    return stepLength * body.size();
}
