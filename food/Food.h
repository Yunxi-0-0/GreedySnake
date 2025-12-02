#pragma once

#include "qpixmap.h"
#include "qsize.h"
#include <QObject>
#include <QPoint>
#include <QSize>

class Food : public QObject
{
    Q_OBJECT
public:
    explicit Food(QObject *parent = nullptr);
    void generate(int x = 0, int y = 0, int width = 10, int height = 10);
    QPoint getPosition() const;
    int getX() const;
    int getY() const;
    QSize getSize() const;

private:
    QPoint position;
    QSize size;
    QPixmap foodPixmap;
};