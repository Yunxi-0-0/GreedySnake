#include "Food.h"
#include "qpoint.h"

Food::Food(QObject *parent) : QObject(parent), position(QPoint(0, 0)), size(QSize(10, 10))
{
    
}

void Food::generate(int x, int y, int width, int height){
    x = rand() % 720;
    y = rand() % 480;
    width = rand() % 30;
    height = rand() % 30;

    position = QPoint(x-width/2, y-height/2);

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