#include "UpBar.h"
#include "qobject.h"
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
    // timeLabel->setText("Time: 00:00:00");

    time = new QTime(0, 0, 0);
    timeLabel->setText(Time + time->toString("hh:mm:ss"));
 
    scoreLabel = new QLabel(this);
    scoreLabel2 = new QLabel(this);
    scoreLabel3 = new QLabel(this);
    scoreLabel->setText(playerName + "Score: " + QString::number(0));
    scoreLabel2->setText(playerName2 + "Score: " + QString::number(0));
    scoreLabel3->setText(playerName3 + "Score: " + QString::number(0));

    playerLayout = new QVBoxLayout();
    playerLayout->addWidget(scoreLabel);
    playerLayout->addWidget(scoreLabel2);
    playerLayout->addWidget(scoreLabel3);

    playerLayout = new QVBoxLayout();
    playerLayout->addWidget(scoreLabel);
    playerLayout->addWidget(scoreLabel2);
    playerLayout->addWidget(scoreLabel3);


    layout = new QHBoxLayout(this);
    layout->addWidget(stopBtn);
    layout->addWidget(startBtn);
    layout->addWidget(timeLabel);
    layout->addLayout(playerLayout);

    this->setLayout(layout);

}

void UpBar::initConnections(){
    connect(stopBtn, &QPushButton::clicked, this, [this](){emit stopGame();});
    connect(startBtn, &QPushButton::clicked, this, [this](){emit startGame();});
    
}

void UpBar::changeScore(int player, int score){
    switch(player){
        case 1:
            this->score = score;
            scoreLabel->setText(playerName + " Score: " + QString::number(score));
            break;
        case 2:
            this->score2 = score;
            scoreLabel2->setText(playerName2 + " Score: " + QString::number(score));
            break;
        case 3:
            this->score3 = score;
            scoreLabel3->setText(playerName3 + " Score: " + QString::number(score));
            break;
        default:
            break;
    }
}

void UpBar::changePlayerName(int player, QString name){
    switch(player){
        case 1:
            playerName = name;
            scoreLabel->setText(playerName + " Score: " + QString::number(0));
            break;
        case 2:
            playerName2 = name;
            scoreLabel2->setText(playerName2 + " Score: " + QString::number(0));
            break;
        case 3:
            playerName3 = name;
            scoreLabel3->setText(playerName3 + " Score: " + QString::number(0));
            break;
        default:
            break;
    }
}

void UpBar::changeLanguage(QString language){
    if(language == "en"){
        stopBtn->setText("Stop");
        startBtn->setText("Start");
        Time = "Time: ";
        timeLabel->setText(Time + time->toString("hh:mm:ss"));
        scoreLabel->setText(playerName + Score + QString::number(0));
        scoreLabel2->setText(playerName2 + Score + QString::number(0));
        scoreLabel3->setText(playerName3 + Score + QString::number(0));
    }
    else if(language == "zh"){
        stopBtn->setText("停止");
        startBtn->setText("开始");  
        Time = "时间: ";
        timeLabel->setText(Time + time->toString("hh:mm:ss"));
        Score = " 分数: ";
        scoreLabel->setText(playerName + Score +QString::number(score));
        scoreLabel2->setText(playerName2 + Score + QString::number(score2));
        scoreLabel3->setText(playerName3 + Score + QString::number(score3));

    }
}

void UpBar::addTime(){
    time->addSecs(1);
    timeLabel->setText(Time + time->toString("hh:mm:ss"));
}