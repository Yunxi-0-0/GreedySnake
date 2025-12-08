#include "Landmine.h"
#include "qpixmap.h"
#include "qpoint.h"
#include "../tools/tools.h"


Landmine::Landmine(QObject *parent) : QObject(parent), position(QPoint(0, 0)), size(QSize(10, 10))
{
    generate();
}
void Landmine::generate(int x, int y, int width, int height){


    landminePixmap = QPixmap(getImagePath("landmine.jpg"));


    x = QRandomGenerator::global()->generate() % 680 + 20;
    y = QRandomGenerator::global()->generate() % 440 + 20;
    // width = QRandomGenerator::global()->generate() % 30 + 10;
    // height = QRandomGenerator::global()->generate() % 30 + 10;
    int Size = QRandomGenerator::global()->generate() % 30 + 10;

    position = QPoint(x-width/2, y-height/2);
    size = QSize(Size, Size);
    isGenerated = true;


}

QPoint Landmine::getPosition() const{
    return position;
}

int Landmine::getX() const{
    return position.x();
}

int Landmine::getY() const{
    return position.y();
}

QSize Landmine::getSize() const{
    return size;
}

QPixmap Landmine::getLandminePixmap() const{
    return landminePixmap;
}

QPixmap Landmine::setLandminePixmap(QString imageName){
    landminePixmap =QPixmap(getImagePath(imageName));
    return landminePixmap;
}




bool Landmine::IsGenerated() const{
    return isGenerated;
}

bool Landmine::setIsGenerated(bool value){
    isGenerated = value;
    return isGenerated;
}



