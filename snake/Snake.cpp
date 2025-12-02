#include "snake.h"
#include "qgraphicsitem.h"
#include "qpoint.h"

Snake::Snake()
{
    head = QPoint(360, 240);
    body.append(head);
    // 将初始身体放在头部的后方，避免第一次移动时重叠
    switch (direction) {
    case UP:
        body.append(head + QPoint(0, size));
        body.append(head + QPoint(0, 2 * size));
        break;
    case DOWN:
        body.append(head + QPoint(0, -size));
        body.append(head + QPoint(0, -2 * size));
        break;
    case LEFT:
        body.append(head + QPoint(size, 0));
        body.append(head + QPoint(2 * size, 0));
        break;
    case RIGHT:
        body.append(head + QPoint(-size, 0));
        body.append(head + QPoint(-2 * size, 0));
        break;
    }

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
        body.insert(0, {head.x(), head.y() - speed});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case DOWN:
        body.insert(0, {head.x(), head.y() + speed});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case LEFT:
        body.insert(0, {head.x() - speed, head.y()});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case RIGHT:
        body.insert(0, {head.x() + speed, head.y()});
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
        body.append(body.last() + QPoint(0, size));
        break;
    case DOWN:
        body.append(body.last() + QPoint(0, -size));
        break;
    case LEFT:
        body.append(body.last() + QPoint(size, 0));
        break;
    case RIGHT:
        body.append(body.last() + QPoint(-size, 0));
        break;
    }
}