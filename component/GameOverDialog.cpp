#include "GameOverDialog.h"
#include "qpixmap.h"
#include <QCoreApplication>
#include "../tools/Tools.h"

GameOverDialog::GameOverDialog(QWidget *parent){
    initUI();
    initConnect();
}

void GameOverDialog::initUI(){
    setWindowTitle("Game Over");
    setFixedSize(300, 300);
    
    imageLabel = new QLabel(this);
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(QPixmap(getImagePath("gameOver.jpg")));
    restartBtn = new QPushButton("Restart", this);
    exitBtn = new QPushButton("Exit", this);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(restartBtn);
    mainLayout->addWidget(exitBtn);
    mainLayout->setAlignment(Qt::AlignCenter);

}

void GameOverDialog::initConnect(){
    connect(restartBtn, &QPushButton::clicked, this, [this](){
        emit restartGame();
        close();
    });
    connect(exitBtn, &QPushButton::clicked, this, [this](){
        emit exitGame();
        close();
    });
}