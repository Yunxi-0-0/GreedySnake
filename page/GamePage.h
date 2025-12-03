#pragma once
#include <QWidget>
#include <QGraphicsWidget>
#include "../component/UpBar.h"
#include "../component/GameArea.h"
#include "qtmetamacros.h"

class GamePage : public QWidget{
    Q_OBJECT
public:
    GamePage(QWidget *parent = nullptr);
private:

    UpBar *upBar;
    GameArea *gameArea;
    GameOverDialog *gameOverDialog;
    void initUI();
    void initConnect();

    bool isRunning = false;

signals:
    void exitGame();

public:
    void startGame();
    
public slots:
    void reset();

};

