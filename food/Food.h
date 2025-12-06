#pragma once

#include "qcontainerfwd.h"
#include "qpixmap.h"
#include "qsize.h"
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QRandomGenerator>
#include <QHash>

class Food : public QObject
{
    Q_OBJECT
public:
    explicit Food(QObject *parent = nullptr);
    enum FoodType {
        Apple,
        Banana,
        Charry,
        Grape,
        GreenGrape,
        Lemon,
        Mango,
        Orange,
        Pomegranate,
        Watermelon,
        
    };
    void generate(int x = 0, int y = 0, int width = 10, int height = 10);
    QPoint getPosition() const;
    int getX() const;
    int getY() const;
    QSize getSize() const;
    QPixmap getFoodPixmap() const;
    QPixmap setFoodPixmap(QString imageName);
    void initFoodImagePath();
    bool IsGenerated() const;
    bool setIsGenerated(bool value);

private:
    QPoint position;
    QSize size;
    FoodType foodType;
    QPixmap foodPixmap;
    QHash<Food::FoodType, QString> foodImagePath;
    FoodType getRandomFoodType() const;
    bool isGenerated = false;

};