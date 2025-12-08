#pragma once

#include "GamePage.h"
#include "../component/GameOverDialog.h"
#include <qaction.h>

GamePage::GamePage(QWidget *parent) : QWidget(parent){
    initUI();
    initConnect();
}

void GamePage::initUI(){
    upBar = new UpBar(this);
    upBar->setFixedHeight(120);

    gameArea = new GameArea(this);
    gameArea->setFixedSize(720,480);
    gameArea->move(0,120);

    gameOverDialog = new GameOverDialog(this);
    gameOverDialog->setWindowModality(Qt::WindowModal);
    gameOverDialog->setWindowTitle("Game Over");
}

void GamePage::initConnect(){
    connect(upBar, &UpBar::startGame, this, [this](){
        gameArea->start();
    });
    connect(upBar, &UpBar::stopGame, this, [this](){
        gameArea->stop();
    });
    connect(gameArea, &GameArea::scoreChanged, upBar, &UpBar::changeScore);
    connect(gameArea, &GameArea::gameOver, this, [this](){
        gameOverDialog->show();
    });
    connect(gameOverDialog, &GameOverDialog::restartGame, gameArea, &GameArea::restart);
    connect(gameOverDialog, &GameOverDialog::exitGame, gameArea, &GameArea::exitGame);
    connect(gameOverDialog, &GameOverDialog::exitGame, this, [this](){
        emit exitGame();
        gameArea->restart();
        gameArea->stop();
    });
    connect(gameArea, &GameArea::backEndSnakeScore, this, &GamePage::backEndScore);
    connect(gameArea, &GameArea::addTime, upBar, &UpBar::addTime);
}

void GamePage::reset(){
    // gameArea->restart();
    
}

void GamePage::setPlayerColour(int player, QAction *action){
    Snake::Colour colour;
    if(action->text() == "Red"){
        colour = Snake::RED;
    }else if(action->text() == "Green"){
        colour = Snake::GREEN;
    }else if(action->text() == "Blue"){
        colour = Snake::BLUE;
    }else if(action->text() == "Yellow"){
        colour = Snake::YELLOW;
    }else if(action->text() == "Black"){
        colour = Snake::BLACK;
    }else if(action->text() == "Magenta"){
        colour = Snake::MAGENTA;
    }
    gameArea->setSnakeColour(player, colour);
}

void GamePage::setPlayerController(int player, QAction *action){
    Snake::Controller controller;
    if(action->text() == "Enabled"){
        controller = Snake::ENABLED;
    }else if(action->text() == "Disabled"){
        controller = Snake::DISABLED;
    }else if(action->text() == "AI"){
        controller = Snake::AI;
    }
    gameArea->setSnakeController(player, controller);
}

void GamePage::backEndScore(Snake *snake){
    emit updateScoreRankings(snake->getName(), snake->getScore());
}

void GamePage::changeDifficulty(int difficulty){
    this->difficulty = difficulty;
    gameArea->setDifficulty(difficulty);
}

void GamePage::changePlayerName(int player, QString name){
    gameArea->setSnakeName(player, name);
    upBar->changePlayerName(player, name);
}

void GamePage::changeLanguage(QString language){
    upBar->changeLanguage(language);
}

void GamePage::changeVolume(double volume){
    gameArea->changeVolume(volume);
}

