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
    this->score = 0;
    generate();
}

Snake::Snake(int size, int speed, int FPS,bool isEnabled, bool isAi, QPoint initialPosition){
    this->size = size;
    this->speed = speed;
    this->FPS = FPS;
    this->score = 0;
    this->initialPosition = initialPosition;
    if(isEnabled&&!isAi){
        this->setController(Snake::ENABLED);
    }else if(isEnabled&&isAi){
        this->setController(Snake::AI);
    }else if(!isEnabled&&!isAi){
        this->setController(Snake::DISABLED);
    }else{
        this->setController(Snake::DISABLED);
    }

    this->generate(initialPosition);

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
        body.insert(0, {head.x(), head.y() - speed/100});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case DOWN:
        body.insert(0, {head.x(), head.y() + speed/100});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case LEFT:
        body.insert(0, {head.x() - speed/100, head.y()});
        body.remove(body.size() - 1);
        head = body.first();
        break;
    case RIGHT:
        body.insert(0, {head.x() + speed/100, head.y()});
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
    if(initialPosition.isNull()){
        initialPosition = QPoint(360, 240);
    }
    head = initialPosition;
    body.append(head);
    // 将初始身体放在头部的后方，避免第一次移动时重叠
    for(int i = 1; i < 50 / stepLength; i++){
        body.append(body.last() + QPoint(0, +stepLength));
    }
    
}

void Snake::generate(QPoint initialPosition){
    direction = UP;
    head = initialPosition;
    body.append(head);
    // 将初始身体放在头部的后方，避免第一次移动时重叠
    for(int i = 1; i < 50 / stepLength; i++){
        body.append(body.last() + QPoint(0, +stepLength));
    }
    if(controller != Snake::DISABLED){
        this->isAlive = true;
    }
}

void Snake::reGenerate(){
    if(!isEnabled){
        return;
    }
    body.clear();
    score = 0;
    emit scoreChanged(score);
    generate(this->initialPosition);
}

int Snake::getSpeed() const{
    return speed;
}

void Snake::setSpeed(int speed){
    this->speed = speed;
}

int Snake::getFPS() const{
    return FPS;
}

void Snake::setFPS(int FPS){
    this->FPS = FPS;
}

int Snake::getStepLength() const{
    return stepLength;
}

int Snake::getTotalLength() const{
    return stepLength * body.size();
}

Snake::Colour Snake::getColour() const{
    return colour;
}

void Snake::setColour(Snake::Colour colour){
    this->colour = colour;
}

bool Snake::IsEnabled() const{
    return isEnabled;
}

void Snake::setEnabled(bool enabled){
    isEnabled = enabled;
}

bool Snake::IsAi() const{
    return isAi;
}

void Snake::setAi(bool isAi){
    this->isAi = isAi;
}

bool Snake::IsAlive() const{
    return isAlive;
}

void Snake::setAlive(bool isAlive){
    this->isAlive = isAlive;
}

QString Snake::getName() const{
    if(!name.isEmpty()){
        return name;
    }
    return "Unnamed Snake";
    
}

void Snake::setName(QString name){
    this->name = name;
}

void Snake::setController(Controller controller){
    if(controller == Snake::AI){
        this->isAi = true;
        this->setEnabled(true);
        this->isAlive = true;
    }else if(controller == Snake::ENABLED){
        this->isAi = false;
        this->setEnabled(true);
        this->isAlive = true;
    }else if(controller == Snake::DISABLED){
        this->isAi = false;
        this->setEnabled(false);
        this->isAlive = false;
    }      
    this->controller = controller;
}

Snake::Controller Snake::getController() const{
    return controller;
}