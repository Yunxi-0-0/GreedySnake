#pragma once
#include "GamePage.h"
#include "../component/GameOverDialog.h"

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
    });
}

void GamePage::reset(){
    // gameArea->restart();
    
}