#include "GameArea.h"
#include "GameOverDialog.h"
#include "qevent.h"
#include "qnamespace.h"
#include "qpainter.h"
#include "qpoint.h"
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMessagebox>

GameArea::GameArea(QWidget *parent) : QWidget(parent){
    snake = new Snake(10,100,FPS);
    snake2 = new Snake(10,100,FPS,false,QPoint(180,240));
    snake3 = new Snake(10,100,FPS,false,QPoint(540,240));
    // snake2 = new Snake(10,100,FPS,Snake::DISABLED,QPoint(180,240));
    // snake3 = new Snake(10,100,FPS,Snake::DISABLED,QPoint(540,240));
    // 允许接收键盘事件
    setFocusPolicy(Qt::StrongFocus);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        if(snake->IsEnabled()){
            snake->move();
        }
        if(snake2->IsEnabled()){
            snake2->move();
        }
        if(snake3->IsEnabled()){
            snake3->move();
        }
        update();
    });
    connect(snake, &Snake::scoreChanged, this, [this](int score){
        emit scoreChanged(score);
    });
    connect(this, &GameArea::gameOver, this, [this](){
        stop();
    });

}

void GameArea::start() {
    timer->start(1000 / FPS);
    is_Running = true;
    setFocus();
}

void GameArea::stop() {
    timer->stop();
    is_Running = false;
}

void GameArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 绘制背景
    painter.fillRect(rect(), Qt::white);

    // 绘制蛇
    printSnake(painter, snake);
    printSnake(painter, snake2);
    printSnake(painter, snake3);


    // 绘制食物
    if(!is_Food_Generated){
        food = new Food();
        food->generate();

        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(food->getX() - food->getSize().width()/2, food->getY() - food->getSize().height()/2, food->getSize().width(), food->getSize().height());
        is_Food_Generated = true;
    }else{
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(food->getX() - food->getSize().width()/2, food->getY() - food->getSize().height()/2, food->getSize().width(), food->getSize().height());

    }

    // 吃到食物后，生成新的食物
    if(checkEatFood(snake, food)){
        is_Food_Generated = false;
        snake->eat(food);
        generateFood();
    }

    // 检测碰撞
    if(checkCollision(snake)){
        emit gameOver();
    }


}

void GameArea::keyPressEvent(QKeyEvent *event) {
    controlSnake(event, snake, Snake::WASD);
    controlSnake(event, snake2, Snake::IJKL);
    controlSnake(event, snake3, Snake::COMMON);

}

bool GameArea::isRunning() const {
    return is_Running;
}

void GameArea::generateFood(){
    if(food == nullptr){
        food = new Food();
    }
    food->generate();
    is_Food_Generated = true;

}

bool GameArea::checkEatFood(Snake *snake, Food *food){
    bool is_Eat = false;
    if(food->getX() <= snake->getHead().x() +snake->getSize()/2 
    && food->getX() >= snake->getHead().x() - snake->getSize()/2 
    && food->getY() <= snake->getHead().y() +snake->getSize()/2 
    && food->getY() >= snake->getHead().y() - snake->getSize()/2){
        is_Eat = true;
    }
    return is_Eat;
}

bool GameArea::checkCollision(Snake *snake){
    bool is_Collision = false;
    // 检测碰撞边缘
    if(snake->getHead().x() < 0 || snake->getHead().x() > 719 || snake->getHead().y() < 0 || snake->getHead().y() > 479){
        is_Collision = true;
    }
    // 检测碰撞自己
    for(int i = 1; i < snake->getBody().size(); i++){
        if(snake->getHead() == snake->getBody()[i]){
            is_Collision = true;
            break;
        }
    }
    return is_Collision;
}

void GameArea::printSnake(QPainter &painter, Snake *snake){
    if(!snake->IsEnabled()){
        return;
    }
    Snake::Colour colour = snake->getColour();
    painter.setBrush(Qt::green);
    painter.setPen(Qt::NoPen);
    switch(colour){
        case Snake::RED:
            painter.setBrush(Qt::red);
            break;
        case Snake::BLUE:
            painter.setBrush(Qt::blue);
            break;
        case Snake::GREEN:
            painter.setBrush(Qt::green);
            break;
        case Snake::YELLOW:
            painter.setBrush(Qt::yellow);
            break;
        case Snake::BLACK:
            painter.setBrush(Qt::black);
            break;
        case Snake::MAGENTA:
            painter.setBrush(Qt::magenta);
            break;
        default:
            break;
    }
    for (const QPoint &snake_part : snake->getBody()) {
        painter.drawEllipse(snake_part.x() - snake->getSize()/2, snake_part.y() - snake->getSize()/2, snake->getSize(), snake->getSize());
    }
}

void GameArea::restart() {
    snake->reGenerate();
    generateFood();
}

void GameArea::exitGame(){
    snake->reGenerate();
}

void GameArea::controlSnake(QKeyEvent *event, Snake *snake, Snake::Control control){
    if(snake !=nullptr){
        if(control == Snake::COMMON) {
        switch (event->key()) {
        case Qt::Key_Up:
            if(snake->getDirection() == Snake::DOWN||!is_Running){
                break;
            }
            snake->setDirection(Snake::UP);
            break;
        case Qt::Key_Down:
            if(snake->getDirection() == Snake::UP||!is_Running){
                break;
           }
            snake->setDirection(Snake::DOWN);
            break;
        case Qt::Key_Left:
            if(snake->getDirection() == Snake::RIGHT||!is_Running){
                break;
            }
            snake->setDirection(Snake::LEFT);
            break;
        case Qt::Key_Right:
            if(snake->getDirection() == Snake::LEFT||!is_Running){
                break;
            }
            snake->setDirection(Snake::RIGHT);
            break;
        case Qt::Key_Space:
             if(isRunning()){
                 stop();
             }else if(!isRunning()){
                 start();
             }
            break;
        default:
            break;
            }
        }
        if(control == Snake::WASD){
            switch (event->key()) {
            case Qt::Key_W:
                if(snake->getDirection() == Snake::DOWN||!is_Running){
                    break;
                }
                snake->setDirection(Snake::UP);
                break;
            case Qt::Key_S:
                if(snake->getDirection() == Snake::UP||!is_Running){
                    break;
                }
                snake->setDirection(Snake::DOWN);
                break;
            case Qt::Key_A:
                if(snake->getDirection() == Snake::RIGHT||!is_Running){
                    break;
                }
                snake->setDirection(Snake::LEFT);
                break;
            case Qt::Key_D:
                if(snake->getDirection() == Snake::LEFT||!is_Running){
                    break;
                }
                snake->setDirection(Snake::RIGHT);
                break;
            }
        }
        if(control == Snake::IJKL){
            switch (event->key()) {
            case Qt::Key_I:
                if(snake->getDirection() == Snake::DOWN||!is_Running){
                    break;
                }
                snake->setDirection(Snake::UP);
                break;
            case Qt::Key_K:
                if(snake->getDirection() == Snake::UP||!is_Running){
                    break;
                }
                snake->setDirection(Snake::DOWN);
                break;
            case Qt::Key_J:
                if(snake->getDirection() == Snake::RIGHT||!is_Running){
                    break;
                }
                snake->setDirection(Snake::LEFT);
                break;
            case Qt::Key_L:
                if(snake->getDirection() == Snake::LEFT||!is_Running){
                    break;
                }
                snake->setDirection(Snake::RIGHT);
                break;
            }
        }
    }
}