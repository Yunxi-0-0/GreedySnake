#include "Food.h"
#include "qpoint.h"


Food::Food(QObject *parent) : QObject(parent), position(QPoint(0, 0)), size(QSize(10, 10))
{
    generate();
}
void Food::generate(int x, int y, int width, int height){
    x = QRandomGenerator::global()->generate() % 720;
    y = QRandomGenerator::global()->generate() % 480;
    width = QRandomGenerator::global()->generate() % 30 + 10;
    height = QRandomGenerator::global()->generate() % 30 + 10;

    position = QPoint(x-width/2, y-height/2);
    size = QSize(width, height);

}

QPoint Food::getPosition() const{
    return position;
}

int Food::getX() const{
    return position.x();
}

int Food::getY() const{
    return position.y();
}

QSize Food::getSize() const{
    return size;
}