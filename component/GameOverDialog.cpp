#include "GameOverDialog.h"
#include "qpixmap.h"
#include <QCoreApplication>

GameOverDialog::GameOverDialog(QWidget *parent){
    initUI();
    initConnect();
}

void GameOverDialog::initUI(){
    setWindowTitle("Game Over");
    setFixedSize(300, 300);
    
    imageLabel = new QLabel(this);
    QDir appDir(QCoreApplication::applicationDirPath());
    QString imageDir = QDir(appDir.filePath("..")).filePath("image/gameOver.jpg");

    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(QPixmap(imageDir));
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