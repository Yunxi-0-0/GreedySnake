#include "Food.h"
#include "qpixmap.h"
#include "qpoint.h"
#include "../tools/tools.h"


Food::Food(QObject *parent) : QObject(parent), position(QPoint(0, 0)), size(QSize(10, 10))
{
    initFoodImagePath();
    generate();
}
void Food::generate(int x, int y, int width, int height){

    FoodType foodType = getRandomFoodType();

    foodPixmap = QPixmap(getImagePath(foodImagePath[foodType]));

    x = QRandomGenerator::global()->generate() % 680 + 20;
    y = QRandomGenerator::global()->generate() % 440 + 20;
    // width = QRandomGenerator::global()->generate() % 30 + 10;
    // height = QRandomGenerator::global()->generate() % 30 + 10;
    int Size = QRandomGenerator::global()->generate() % 30 + 10;

    position = QPoint(x-width/2, y-height/2);
    size = QSize(Size, Size);
    isGenerated = true;


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

QPixmap Food::getFoodPixmap() const{
    return foodPixmap;
}

QPixmap Food::setFoodPixmap(QString imageName){
    foodPixmap =QPixmap(getImagePath(imageName));
    return foodPixmap;
}

void Food::initFoodImagePath(){
    foodImagePath={
        {FoodType::Apple, "apple.png"},
        {FoodType::Banana, "banana.png"},
        {FoodType::Charry, "charry.png"},
        {FoodType::Grape, "grape.png"},
        {FoodType::GreenGrape, "greenGrape.png"},
        {FoodType::Lemon, "lemon.png"},
        {FoodType::Mango, "mango.png"},
        {FoodType::Orange, "orange.png"},
        {FoodType::Pomegranate, "pomegranate.png"},
        {FoodType::Watermelon, "watermelon.png"}
        
    };
}

Food::FoodType Food::getRandomFoodType() const{
    int foodType = QRandomGenerator::global()->generate() % 10;
    switch(foodType){
        case 0:
            return FoodType::Apple;
        case 1:
            return FoodType::Banana;
        case 2:
            return FoodType::Charry;
        case 3:
            return FoodType::Grape;
        case 4:
            return FoodType::GreenGrape;
        case 5:
            return FoodType::Lemon;
        case 6:
            return FoodType::Mango;
        case 7:
            return FoodType::Orange;
        case 8:
            return FoodType::Pomegranate;
        case 9:
            return FoodType::Watermelon;
    }
    return FoodType::Apple;
}

bool Food::IsGenerated() const{
    return isGenerated;
}

bool Food::setIsGenerated(bool value){
    isGenerated = value;
    return isGenerated;
}