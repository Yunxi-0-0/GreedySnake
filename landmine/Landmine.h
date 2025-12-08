#pragma once

#include "qcontainerfwd.h"
#include "qpixmap.h"
#include "qsize.h"
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QRandomGenerator>
#include <QHash>

class Landmine : public QObject
{
    Q_OBJECT
public:
    explicit Landmine(QObject *parent = nullptr);
    void generate(int x = 0, int y = 0, int width = 10, int height = 10);
    QPoint getPosition() const;
    int getX() const;
    int getY() const;
    QSize getSize() const;
    QPixmap getLandminePixmap() const;
    QPixmap setLandminePixmap(QString imageName);
    bool IsGenerated() const;
    bool setIsGenerated(bool value);

private:
    QPixmap landminePixmap;
    QPoint position;
    QSize size;
    bool isGenerated = false;

};