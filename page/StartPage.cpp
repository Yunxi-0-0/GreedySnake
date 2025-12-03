#include "StartPage.h"
#include "qdebug.h"


StartPage::StartPage(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnections();
}

void StartPage::initUI(){
    mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel("Greedy Snake", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 32px; font-weight: bold;");

    startButton = new QPushButton("Start Game", this);
    startButton->setFixedSize(250,75);

    settingsButton = new QPushButton("Settings", this);
    settingsButton->setFixedSize(200, 75);

    exitButton = new QPushButton("Exit", this);
    exitButton->setFixedSize(150, 75);

    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(startButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(settingsButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(exitButton, 0, Qt::AlignCenter);

    mainLayout->setAlignment(Qt::AlignCenter);
    setLayout(mainLayout);
}

void StartPage::initConnections(){
    connect(startButton, &QPushButton::clicked, this, [this](){
        emit StartPageStart();
    });
    connect(settingsButton, &QPushButton::clicked, this, [this](){
        emit StartPageSettings();     
    });
    connect(exitButton, &QPushButton::clicked, this, [this](){
        emit StartPageExit();
    });
}