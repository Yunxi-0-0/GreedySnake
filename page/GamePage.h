#pragma once
#include <QWidget>
#include <QGraphicsWidget>
#include "../component/UpBar.h"
#include "../component/GameArea.h"

class GamePage : public QWidget{
    Q_OBJECT
public:
    GamePage(QWidget *parent = nullptr);
private:

    UpBar *upBar;
    GameArea *gameArea;
    void initUI();
    void initConnect();

    bool isRunning = false;

};

