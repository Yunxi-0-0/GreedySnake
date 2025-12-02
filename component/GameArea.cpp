#include "GameArea.h"
#include "qnamespace.h"
#include <QPaintEvent>
#include <QKeyEvent>

GameArea::GameArea(QWidget *parent) : QWidget(parent){
    snake = new Snake();
    // 允许接收键盘事件
    setFocusPolicy(Qt::StrongFocus);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        snake->move();
        update();
    });
    connect(snake, &Snake::scoreChanged, this, [this](int score){
        emit scoreChanged(score);
    });
}

void GameArea::start() {
    timer->start(100);
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
    for (const QPoint &snake_part : snake->getBody()) {
        painter.setBrush(Qt::green);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(snake_part.x() - 5, snake_part.y() - 5, 10, 10);
    }

    // 绘制食物
    if(!is_Food_Generated){
        food = new Food();
        food->generate();

        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(food->getX() - 5, food->getY() - 5, 10, 10);
        is_Food_Generated = true;
    }else{
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(food->getX() - 5, food->getY() - 5, 10, 10);
    }

    // 吃到食物后，生成新的食物
    if(checkEatFood(snake, food)){
        is_Food_Generated = false;
        snake->eat(food);
        generateFood();
    }

    // // 检测碰撞
    // if(checkCollision(snake)){
    //     stop();
    //     emit gameOver();
    // }


}

void GameArea::keyPressEvent(QKeyEvent *event) {
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

bool GameArea::isRunning() const {
    return is_Running;
}

void GameArea::generateFood(){
    if(food == nullptr){
    food = new Food();
    food->generate();
    is_Food_Generated = true;
    }else{
        delete food;
        food = new Food();
        food->generate();
        is_Food_Generated = true;
    }

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
