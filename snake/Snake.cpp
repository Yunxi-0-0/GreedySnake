#include "snake.h"
#include "qgraphicsitem.h"
#include "qpoint.h"
#include "qtmetamacros.h"
#include <QQueue>


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
    if(controller == Snake::AI){
        if(route.isEmpty()){
            return;
        }
        QPoint next = route.first();
        if(next.x() < head.x()){
                direction = LEFT;
        }else if(next.x() > head.x()){
                direction = RIGHT;
        }else if(next.y() < head.y()){
                direction = UP;
        }else if(next.y() > head.y()){
                direction = DOWN;
        }
        route.remove(0);
    }
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
        score += food->getScore();
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

// QPoint 哈希函数，让 QPoint 可以作为 QHash/QSet 的键
inline uint qHash(const QPoint &key, uint seed = 0) {
    return qHash(QPair<int,int>(key.x(), key.y()), seed);
}

// 节点结构
struct Node {
    QPoint pos;
    int g; // 已走的代价
    int h; // 启发式估计
    int f() const { return g + h; }
};

void Snake::routePlanning(QVector<QPoint> obstacles, QVector<Food*> foods){
    if(difficulty == 1){
        QPoint  hithermostFood = foods.first()->getPosition();
        for(auto food : foods){
            if(abs(food->getPosition().x()-this->head.x())+abs(food->getPosition().y()-this->head.y()) < abs(hithermostFood.x()-this->head.x())+abs(+hithermostFood.y()-this->head.y())){
                hithermostFood = food->getPosition();
            }
        }
        QVector<QPoint> route;
        QPoint current = head;
        for(int i=1 ;i<= abs(hithermostFood.x()-this->head.x()) ;i++){
            if(hithermostFood.x() > this->head.x()){
                route.append(current += QPoint(i,0));
            }else if(hithermostFood.x() < this->head.x()){
                route.append(current += QPoint(-i,0));
            }
        }
        for(int i=1 ;i<= abs(hithermostFood.y()-this->head.y()) ;i++){
            if(hithermostFood.y() > this->head.y()){
                route.append(current += QPoint(0,i));
            }else if(hithermostFood.y() < this->head.y()){
                route.append(current += QPoint(0,-i));
            }
        }
        this->route = route;
    }else if(difficulty == 2){
                // 找最近的食物
    QPoint target = foods.first()->getPosition();
    for(auto food : foods){
        int distFood = abs(food->getPosition().x() - head.x()) + abs(food->getPosition().y() - head.y());
        int distCurrent = abs(target.x() - head.x()) + abs(target.y() - head.y());
        if(distFood < distCurrent){
            target = food->getPosition();
        }
    }

    // 用 QSet 加快障碍查找
    QSet<QPoint> obstacleSet(obstacles.begin(), obstacles.end());

    QVector<QPoint> route;
    QPoint current = head;

    int maxSteps = 500; // 安全限制，避免死循环
    while(current != target && maxSteps-- > 0){
        QPoint next = current;

        // 贪心靠近目标
        if(target.x() < current.x()) next.setX(current.x() - 1);
        else if(target.x() > current.x()) next.setX(current.x() + 1);
        else if(target.y() < current.y()) next.setY(current.y() - 1);
        else if(target.y() > current.y()) next.setY(current.y() + 1);

        // 如果下一步是障碍，尝试绕开一格
        if(obstacleSet.contains(next)){
            bool moved = false;
            QVector<QPoint> alternatives = {
                QPoint(current.x(), current.y() + 1),
                QPoint(current.x(), current.y() - 1),
                QPoint(current.x() + 1, current.y()),
                QPoint(current.x() - 1, current.y())
            };
            for(auto alt : alternatives){
                if(!obstacleSet.contains(alt)){
                    next = alt;
                    moved = true;
                    break;
                }
            }
            if(!moved) break; // 完全绕不开，退出
        }

        route.push_back(next);
        current = next;
    }

    this->route = route;
    }else if(difficulty == 3){
    

    

        // Step 1: 找到最近的食物
        QPoint target = foods.first()->getPosition();
        for(auto food : foods){
            int distFood = abs(food->getPosition().x() - head.x()) + abs(food->getPosition().y() - head.y());
            int distCurrent = abs(target.x() - head.x()) + abs(target.y() - head.y());
            if(distFood < distCurrent){
                target = food->getPosition();
            }
        }

        // Step 2: 初始化
        QSet<QPoint> obstacleSet(obstacles.begin(), obstacles.end());
        QHash<QPoint, QPoint> parent;
        QMultiMap<int, Node> open;   // 按 f 排序
        QSet<QPoint> closed;

        Node start{head, 0, abs(target.x()-head.x()) + abs(target.y()-head.y())};
        open.insert(start.f(), start);
        parent.insert(head, QPoint(-1,-1));

        QVector<QPoint> directions = { {1,0}, {-1,0}, {0,1}, {0,-1} };

        // Step 3: A* 循环
        while(!open.isEmpty()){
            auto it = open.begin();   // f 最小的节点
            Node current = it.value();
            open.erase(it);

            if(closed.contains(current.pos)) continue;
            closed.insert(current.pos);

            if(current.pos == target) break;

            for(auto dir : directions){
                QPoint next = current.pos + dir;
                if(obstacleSet.contains(next)) continue;
                if(closed.contains(next)) continue;

               int g = current.g + 1;
               int h = abs(target.x()-next.x()) + abs(target.y()-next.y());
                Node neighbor{next, g, h};

                if(!parent.contains(next)) {
                    parent.insert(next, current.pos);
                    open.insert(neighbor.f(), neighbor);
                }
            }
        }

        // Step 4: 回溯路径，生成逐步坐标序列
        QVector<QPoint> route;
        QPoint step = target;
        while(step != QPoint(-1,-1)){
            route.push_front(step);
            step = parent.value(step, QPoint(-1,-1));
        }

        // 去掉第一个点（就是 head 本身），避免蛇原地不动
        if(!route.isEmpty() && route.first() == head){
            route.removeFirst();
        }

        this->route = route;
    }
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

void Snake::setDifficulty(int difficulty){
    this->difficulty = difficulty;
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