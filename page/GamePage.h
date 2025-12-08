#pragma once
#include <QWidget>
#include <QGraphicsWidget>
#include <qaction.h>
#include "../component/UpBar.h"
#include "../component/GameArea.h"
#include "qobject.h"
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
    int difficulty = 2;

signals:
    void exitGame();
    void updateScoreRankings(QString playerName, int score);

public:
    void startGame();
    
public slots:
    void reset();
    void setPlayerColour(int player, QAction *action);
    void setPlayerController(int player, QAction *action);
    void backEndScore(Snake *snake);
    void changeDifficulty(int difficulty);
    void changePlayerName(int player, QString name);
    void changeLanguage(QString language);
    void changeVolume(double volume);

};

