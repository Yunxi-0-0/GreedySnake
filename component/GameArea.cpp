#include "GameArea.h"
#include "qcontainerfwd.h"
#include "qevent.h"
#include "qnamespace.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qtmetamacros.h"
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMessagebox>
#include <qaction.h>
#include "../tools/Tools.h"

GameArea::GameArea(QWidget *parent) : QWidget(parent){
    snake = new Snake(10,this->speed,FPS,true,false,QPoint(180,240));
    snake2 = new Snake(10,this->speed,FPS,false,false,QPoint(360,240));
    snake3 = new Snake(10,this->speed,FPS,false,false,QPoint(540,240));

    diedAudioOutput = new QAudioOutput(this);
    diedAudioOutput->setVolume(0.5);

    diedMediaPlayer = new QMediaPlayer(this);
    diedMediaPlayer->setAudioOutput(diedAudioOutput);
    diedMediaPlayer->setSource(QUrl::fromLocalFile(getMusicPath("die.mp3")));

    eatAudioOutput = new QAudioOutput(this);
    eatAudioOutput->setVolume(0.5);

    eatMediaPlayer = new QMediaPlayer(this);
    eatMediaPlayer->setAudioOutput(eatAudioOutput);
    eatMediaPlayer->setSource(QUrl::fromLocalFile(getMusicPath("eat.mp3")));
    

    // 允许接收键盘事件
    setFocusPolicy(Qt::StrongFocus);
    timer = new QTimer(this);
    foodTimer = new QTimer(this);
    landmineTimer = new QTimer(this);
    Timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        if(snake->IsEnabled()&&snake->IsAlive()){
            if(snake->IsAi()){
                QVector<Food*> foods;
                for(auto food : this->foods){
                    foods.append(food);
                }
                foods.append(this->food);
                snake->routePlanning(getObstacles(), foods);
            }
            snake->move();
        }
        if(snake2->IsEnabled()&&snake2->IsAlive()){
            if(snake2->IsAi()){
                QVector<Food*> foods;
                for(auto food : this->foods){
                    foods.append(food);
                }
                foods.append(this->food);
                snake2->routePlanning(getObstacles(), foods);
            }
            snake2->move();
        }
        if(snake3->IsEnabled()&&snake3->IsAlive()){
            if(snake3->IsAi()){
                QVector<Food*> foods;
                for(auto food : this->foods){
                    foods.append(food);
                }
                foods.append(this->food);
                snake3->routePlanning(getObstacles(), foods);
            }
            snake3->move();
        }
        update();
    });
    connect(foodTimer, &QTimer::timeout, this, [this](){
        addFood();
    });
    connect(landmineTimer, &QTimer::timeout, this, [this](){
        addLandmine();
    });
    connect(Timer, &QTimer::timeout, this, [this](){
        emit addTime();
    });
    connect(snake, &Snake::scoreChanged, this, [this](int score){
        emit scoreChanged(1,score);
    });
    connect(snake2, &Snake::scoreChanged, this, [this](int score){
        emit scoreChanged(2,score);
    });
    connect(snake3, &Snake::scoreChanged, this, [this](int score){
        emit scoreChanged(3,score);
    });
    connect(this, &GameArea::gameOver, this, [this](){
        stop();

    });
    connect(this, &GameArea::snakeCollided, this, &GameArea::snakeDied);

}

void GameArea::start() {
    timer->start(1000 / FPS);
    foodTimer->start(10000);
    landmineTimer->start(20000);
    Timer->start(1000);
    is_Running = true;
    setFocus();
}

void GameArea::stop() {
    timer->stop();
    foodTimer->stop();
    landmineTimer->stop();
    Timer->stop();
    is_Running = false;
}

void GameArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 绘制背景
    painter.fillRect(rect(), Qt::white);

    // 绘制食物
    if(!is_Food_Generated){
        food = new Food();
        food->generate();
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(food->getX() - food->getSize().width()/2, food->getY() - food->getSize().height()/2, food->getSize().width(), food->getSize().height(), food->getFoodPixmap());
        is_Food_Generated = true;
    }else{
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(food->getX() - food->getSize().width()/2, food->getY() - food->getSize().height()/2, food->getSize().width(), food->getSize().height(), food->getFoodPixmap());
    }

    for(auto food : foods){
        printFood(painter, food);
    }

    //绘制地雷
    for(auto landmine : landmines){
        printLandmine(painter, landmine);
    }

    // 绘制蛇
    printSnake(painter, snake);
    printSnake(painter, snake2);
    printSnake(painter, snake3);

    // 全部检测
    totalCheck();

}



void GameArea::keyPressEvent(QKeyEvent *event) {
    controlSnake(event, snake, Snake::WASD);
    controlSnake(event, snake2, Snake::IJKL);
    controlSnake(event, snake3, Snake::COMMON);
    control(event);

}

bool GameArea::isRunning() const {
    return is_Running;
}

int GameArea::getSnakeNumber() const {
    int number = 0;
    if(snake->IsAlive()){
        number++;
    }
    if(snake2->IsAlive()){
        number++;
    }
    if(snake3->IsAlive()){
        number++;
    }
    return number;
}

void GameArea::generateFood(){
    if(food == nullptr){
        food = new Food();
    }
    food->generate();
    is_Food_Generated = true;
    for(auto food : foods){
        if(!food->IsGenerated()){
            food->generate();
        }
    }
}

void GameArea::generateFood(Food *food){
    if(food == nullptr){
        food = new Food();
    }
    food->generate();
    food->setIsGenerated(true);
}

void GameArea::addFood(){
    if(foods.size()+1 >= foodLimit){
        return;
    }
    Food *food = new Food();
    foods.append(food);
    food->generate();
}

void GameArea::addLandmine(){
    if(landmines.size() >= landmineLimit){
        return;
    }
    Landmine *landmine = new Landmine();
    landmines.append(landmine);
    landmine->generate();
}

void GameArea::removeFood(Food *food){
    stop();
    if(food == nullptr){
        return;
    }

    delete food;
    foods.removeOne(food);
    start();
}

void GameArea::removeLandmine(Landmine *landmine){
    stop();
    if(landmine == nullptr){
        return;
    }
    delete landmine;
    landmines.removeOne(landmine);
    start();
}

void GameArea::totalCheck(){
    // 吃到食物后，生成新的食物
   if(checkEatFood(snake, food)){
        is_Food_Generated = false;
        snake->eat( food);
        generateFood();
        eatMediaPlayer->play();
    }

    if(checkEatFood(snake2, food)){
        is_Food_Generated = false;
        snake2->eat(food);
        generateFood();
        eatMediaPlayer->play();
    }

    if(checkEatFood(snake3, food)){
        is_Food_Generated = false;
        snake3->eat(food);
        generateFood();
        eatMediaPlayer->play();
    }

    checkEatFood(snake, foods);
    checkEatFood(snake2, foods);
    checkEatFood(snake3, foods);

    checkEatLandmine(snake, landmines);
    checkEatLandmine(snake2, landmines);
    checkEatLandmine(snake3, landmines);

    // 检测碰撞
    if(checkCollision(snake)){
        emit snakeCollided(snake);
    }
    if(checkCollision(snake2)){
        emit snakeCollided(snake2);
    }
    if(checkCollision(snake3)){
        emit snakeCollided(snake3);
    }
    if(checkCollisionBetweenSnakes(snake, snake2)){
        emit snakeCollided(snake);
    }
    if(checkCollisionBetweenSnakes(snake, snake3)){
        emit snakeCollided(snake);
    }
    if(checkCollisionBetweenSnakes(snake2, snake3)){
        emit snakeCollided(snake2);
    }
    if(checkCollisionBetweenSnakes(snake2, snake)){
        emit snakeCollided(snake2);
    }
    if(checkCollisionBetweenSnakes(snake3, snake)){
        emit snakeCollided(snake3);
    }
    if(checkCollisionBetweenSnakes(snake3, snake2)){
        emit snakeCollided(snake3);
    }
    if(!snake->IsAlive()&&!snake2->IsAlive()&&!snake3->IsAlive()){
        emit gameOver();
    }
}

bool GameArea::checkEatFood(Snake *snake, Food *food){
    bool is_Eat = false;
    double distance = sqrt(pow(food->getX() - snake->getHead().x(), 2) + pow(food->getY() - snake->getHead().y(), 2));
    if(distance < (snake->getSize() + food->getSize().width()/2)*0.8){
        is_Eat = true;
    }
    return is_Eat;
}

void GameArea::checkEatFood(Snake *snake, QVector<Food *> foods){
    for(auto food : foods){
        if(checkEatFood(snake, food)){
            snake->eat(food);
            food->generate();
            eatMediaPlayer->play();
        }
    }
}

bool GameArea::checkEatLandmine(Snake *snake, Landmine *landmine){
    bool is_Eat = false;
    double distance = sqrt(pow(landmine->getX() - snake->getHead().x(), 2) + pow(landmine->getY() - snake->getHead().y(), 2));
    if(distance < (snake->getSize() + landmine->getSize().width()/2)*0.8){
        is_Eat = true;
    }
    return is_Eat;
}

void GameArea::checkEatLandmine(Snake *snake, QVector<Landmine *> landmines){
    for(auto landmine : landmines){
        if(checkEatLandmine(snake, landmine)){
            diedMediaPlayer->play();
            emit snakeCollided(snake);
            return;
        }
    }
}

bool GameArea::checkCollision(Snake *snake){
    if(!snake->IsEnabled()||!snake->IsAlive()){
        return false;
    }
    bool is_Collision = false;
    // 检测碰撞边缘
    if(snake->getHead().x() < 0 || snake->getHead().x() > 719 || snake->getHead().y() < 0 || snake->getHead().y() > 479){
        is_Collision = true;
        return is_Collision;
    }
    // 检测碰撞自己
    for(int i = 1; i < snake->getBody().size(); i++){
        if(snake->getHead() == snake->getBody()[i]){
            is_Collision = true;
            return is_Collision;
        }
    }
    return is_Collision;
}

bool GameArea::checkCollisionBetweenSnakes(Snake *snake1, Snake *snake2){
    if(!snake2->IsAlive()||!snake1->IsAlive()||!snake2->IsEnabled()||!snake1->IsEnabled()){
        return false;
    }
    bool is_Collision = false;
    for(int i = 1; i < snake2->getBody().size(); i++){
        if(snake1->getHead() == snake2->getBody()[i]){
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

void GameArea::printFood(QPainter &painter, Food *food){
    if(!is_Food_Generated){
        food = new Food();
        food->generate();
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(food->getX() - food->getSize().width()/2, food->getY() - food->getSize().height()/2, food->getSize().width(), food->getSize().height(), food->getFoodPixmap());
        is_Food_Generated = true;
    }else{
        painter.setBrush(Qt::red);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(food->getX() - food->getSize().width()/2, food->getY() - food->getSize().height()/2, food->getSize().width(), food->getSize().height(), food->getFoodPixmap());

    }
}

void GameArea::printLandmine(QPainter &painter, Landmine *landmine){
    if(landmine == nullptr){
        return;
    }
    painter.setPen(Qt::NoPen);
    painter.drawPixmap(landmine->getX() - landmine->getSize().width()/2, landmine->getY() - landmine->getSize().height()/2, landmine->getSize().width(), landmine->getSize().height(), landmine->getLandminePixmap());
}

void GameArea::restart() {
    snake->reGenerate();
    snake2->reGenerate();
    snake3->reGenerate();
    for(auto food : foods){
        removeFood(food);
    }
    for(auto landmine : landmines){
        removeLandmine(landmine);
    }
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

void GameArea::control(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape:
        stop();
        exitGame();
        break;
    case Qt::Key_R:
        stop();
        restart();
        break;
    case Qt::Key_Space:
        if(isRunning()){
            stop();
        }else if(!isRunning()){
            start();
        }
         break;
    case Qt::Key_F1:
        this->FPS *= 2;
        this->timer->setInterval(1000 / this->FPS);
        snake->setFPS(this->FPS);
        snake2->setFPS(this->FPS);
        snake3->setFPS(this->FPS);
        break;
    case Qt::Key_F2:
        this->FPS /= 2;
        this->timer->setInterval(1000 / this->FPS);
        snake->setFPS(this->FPS);
        snake2->setFPS(this->FPS);
        snake3->setFPS(this->FPS);
        break;
    default:
        break;
    }

}

QVector<QPoint> GameArea::getObstacles() const {
    QVector<QPoint> obstacles;
    if(snake->IsEnabled()&&snake->IsAlive()){
        obstacles.append(snake->getBody());
    }
    if(snake2->IsEnabled()&&snake2->IsAlive()){
        obstacles.append(snake2->getBody());
    }
    if(snake3->IsEnabled()&&snake3->IsAlive()){
        obstacles.append(snake3->getBody());
    }
    for(auto landmine : landmines){
        QPoint landmine_(landmine->getX(), landmine->getY());
        obstacles.append(landmine_);
    }
    return obstacles;
}

void GameArea::backEnd(){
    emit backEndSnakeScore(snake);
    emit backEndSnakeScore(snake2);
    emit backEndSnakeScore(snake3);
}

QString GameArea::getPlayerName(int Player) const{
    QString name;
    if(Player == 1){
        name = snake->getName();
    }
    if(Player == 2){
        name = snake2->getName();
    }
    if(Player == 3){
        name = snake3->getName();
    }
    return name;
}




void GameArea::setSnakeColour(int Player, Snake::Colour colour){
    if(Player == 1){
        snake->setColour(colour);
    }
    if(Player == 2){
        snake2->setColour(colour);
    }
    if(Player == 3){
        snake3->setColour(colour);
    }
}

void GameArea::setSnakeController(int Player, Snake::Controller controller){
    if(Player == 1){
        snake->setController(controller);
    }
    if(Player == 2){
        snake2->setController(controller);
    }
    if(Player == 3){
        snake3->setController(controller);
    }
}

void GameArea::setSnakeName(int Player, QString name){
    if(Player == 1){
        snake->setName(name);
    }
    if(Player == 2){
        snake2->setName(name);
    }
    if(Player == 3){
        snake3->setName(name);
    }
}

void GameArea::snakeDied(Snake *snake){
    snake->setAlive(false);
    this->diedMediaPlayer->play();
}

void GameArea::setDifficulty(int difficulty){
    this->difficulty = difficulty;
    if(difficulty == 1){
        this->landmineLimit = 0;
    }else if(difficulty == 2){
        this->landmineLimit = 5;
    }else {
        this->landmineLimit = 25;
    }
}

void GameArea::playDiedSound(){
    diedMediaPlayer->play();
}

void GameArea::changeVolume(double volume){
    this->eatAudioOutput->setVolume(volume);
    this->diedAudioOutput->setVolume(volume);
}

