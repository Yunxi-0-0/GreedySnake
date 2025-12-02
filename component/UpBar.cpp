#include "UpBar.h"
#include "qtmetamacros.h"

UpBar::UpBar(QWidget *parent) : QWidget(parent){
    
    initUI();
    initConnections();
}

void UpBar::initUI(){

    this->setFixedWidth(720);

    stopBtn = new QPushButton(this);
    stopBtn->setText("Stop");

    startBtn = new QPushButton(this);
    startBtn->setText("Start");

    timeLabel = new QLabel(this);
    timeLabel->setText("Time: 00:00:00");
 
    scoreLabel = new QLabel(this);
    scoreLabel->setText("Score: 0");

    layout = new QHBoxLayout(this);
    layout->addWidget(stopBtn);
    layout->addWidget(startBtn);
    layout->addWidget(timeLabel);
    layout->addWidget(scoreLabel);

    this->setLayout(layout);

}

void UpBar::initConnections(){
    connect(stopBtn, &QPushButton::clicked, this, [this](){emit stopGame();});
    connect(startBtn, &QPushButton::clicked, this, [this](){emit startGame();});
    
}

void UpBar::changeScore(int score){
    scoreLabel->setText(QString("Score: %1").arg(score));
}