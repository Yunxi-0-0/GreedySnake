#pragma once
#include "GamePage.h"
#include "qnamespace.h"

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

}

void GamePage::initConnect(){
    connect(upBar, &UpBar::startGame, this, [this](){
        gameArea->start();
    });
    connect(upBar, &UpBar::stopGame, this, [this](){
        gameArea->stop();
    });
    connect(gameArea, &GameArea::scoreChanged, upBar, &UpBar::changeScore);

}

