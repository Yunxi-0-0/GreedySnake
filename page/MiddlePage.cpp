#include "MiddlePage.h"
#include "qaction.h"
#include "qdir.h"
#include "qlabel.h"
#include "qmessagebox.h"
#include "qpixmap.h"
#include "qpushbutton.h"
#include "qmenu.h"
#include <QApplication>
#include <QDir>
#include <QCoreApplication>
#include <QPixmap>
#include <qtmetamacros.h>
#include "../tools/Tools.h"

MiddlePage::MiddlePage(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnections();
}

void MiddlePage::initUI()
{
    mainLayout = new QVBoxLayout(this);
    playerLayout = new QHBoxLayout();

    player1 = new QLabel("Player 1:");
    player2 = new QLabel("Player 2:");
    player3 = new QLabel("Player 3:");

    playerImage1 = new QLabel(this);
    playerImage1->setScaledContents(true);
    playerImage1->setPixmap(QPixmap(getImagePath("green.jpg")));

    playerImage2 = new QLabel(this);
    playerImage2->setScaledContents(true);
    playerImage2->setPixmap(QPixmap(getImagePath("notEnabled.jpg")));

    playerImage3 = new QLabel(this);
    playerImage3->setScaledContents(true);
    playerImage3->setPixmap(QPixmap(getImagePath("notEnabled.jpg")));

    playerColour1 = new QToolButton(this);
    playerColour1->setText("Green");
    playerColour1->setPopupMode(QToolButton::InstantPopup);
    playerColour2 = new QToolButton(this);
    playerColour2->setText("colour");
    playerColour2->setPopupMode(QToolButton::InstantPopup);
    playerColour3 = new QToolButton(this);
    playerColour3->setText("colour");
    playerColour3->setPopupMode(QToolButton::InstantPopup);

    playerName1 = new QLineEdit(this);
    playerName2 = new QLineEdit(this);
    playerName2->setReadOnly(true);
    playerName3 = new QLineEdit(this);
    playerName3->setReadOnly(true);

    controlMenu1 = new QMenu(this);
    controlMenu1->addAction("Enabled");
    controlMenu1->addAction("Disabled");
    controlMenu1->addAction("AI");
    controlMenu2 = new QMenu(this);
    controlMenu2->addAction("Enabled");
    controlMenu2->addAction("Disabled");
    controlMenu2->addAction("AI");
    controlMenu3 = new QMenu(this);
    controlMenu3->addAction("Enabled");
    controlMenu3->addAction("Disabled");
    controlMenu3->addAction("AI");

    playerControl1 = new QToolButton(this);
    playerControl1->setMenu(controlMenu1);
    playerControl1->setPopupMode(QToolButton::InstantPopup);
    playerControl1->setText("Enabled");

    playerControl2 = new QToolButton(this);
    playerControl2->setMenu(controlMenu2);
    playerControl2->setPopupMode(QToolButton::InstantPopup);
    playerControl2->setText("Disabled");

    playerControl3 = new QToolButton(this);
    playerControl3->setMenu(controlMenu3);
    playerControl3->setPopupMode(QToolButton::InstantPopup);
    playerControl3->setText("Disabled");

    playerLayout1 = new QVBoxLayout();
    playerLayout2 = new QVBoxLayout();
    playerLayout3 = new QVBoxLayout();

    playerLayout1->addWidget(player1);
    playerLayout1->addWidget(playerImage1);
    playerLayout1->addWidget(playerColour1);
    playerLayout1->addWidget(playerName1);
    playerLayout1->addWidget(playerControl1);

    playerLayout2->addWidget(player2);
    playerLayout2->addWidget(playerImage2);
    playerLayout2->addWidget(playerColour2);
    playerLayout2->addWidget(playerName2);
    playerLayout2->addWidget(playerControl2);

    playerLayout3->addWidget(player3);
    playerLayout3->addWidget(playerImage3);
    playerLayout3->addWidget(playerColour3);
    playerLayout3->addWidget(playerName3);
    playerLayout3->addWidget(playerControl3);

    colourMenu1 = new QMenu(this);
    colourMenu1->addAction("Red");
    colourMenu1->addAction("Green");
    colourMenu1->addAction("Blue");
    colourMenu1->addAction("Yellow");
    colourMenu1->addAction("Black");
    colourMenu1->addAction("Magenta");

    colourMenu2 = new QMenu(this);
    colourMenu2->addAction("Red");
    colourMenu2->addAction("Green");
    colourMenu2->addAction("Blue");
    colourMenu2->addAction("Yellow");
    colourMenu2->addAction("Black");
    colourMenu2->addAction("Magenta");


    colourMenu3 = new QMenu(this);
    colourMenu3->addAction("Red");
    colourMenu3->addAction("Green");
    colourMenu3->addAction("Blue");
    colourMenu3->addAction("Yellow");
    colourMenu3->addAction("Black");
    colourMenu3->addAction("Magenta");

    playerColour1->setMenu(colourMenu1);
    playerColour2->setMenu(colourMenu2);
    playerColour3->setMenu(colourMenu3);


    playerLayout->addLayout(playerLayout1);
    playerLayout->addLayout(playerLayout2);
    playerLayout->addLayout(playerLayout3);

    startButton = new QPushButton("Start Game");
    exitButton = new QPushButton("Exit");

    mainLayout->addLayout(playerLayout);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(exitButton);

}

void MiddlePage::initConnections(){
    connect(startButton, &QPushButton::clicked, this, [this](){
        if(getPlayerNumber() >= 1){
            emit startGame();
        }else{
            QMessageBox::warning(this, "Warning", "Please select at least one player");
        }
    });
    connect(exitButton, &QPushButton::clicked, this, [this](){
        emit exitGame();
    });
    connect(colourMenu1, &QMenu::triggered, this, &MiddlePage::MiddlePage::changePlayerColour1);
    connect(colourMenu2, &QMenu::triggered, this, &MiddlePage::MiddlePage::changePlayerColour2);
    connect(colourMenu3, &QMenu::triggered, this, &MiddlePage::MiddlePage::changePlayerColour3);
    connect(playerControl1, &QToolButton::triggered, this, &MiddlePage::MiddlePage::changePlayerControl1);
    connect(playerControl2, &QToolButton::triggered, this, &MiddlePage::MiddlePage::changePlayerControl2);
    connect(playerControl3, &QToolButton::triggered, this, &MiddlePage::MiddlePage::changePlayerControl3);
    connect(playerName1, &QLineEdit::textChanged, this, [this](QString text){
        emit changePlayerName(1, text);
    });
    connect(playerName2, &QLineEdit::textChanged, this, [this](QString text){
        emit changePlayerName(2, text);
    }); 
    connect(playerName3, &QLineEdit::textChanged, this, [this](QString text){
        emit changePlayerName(3, text);
    }); 
}

void MiddlePage::changePlayerColour1(QAction *action){
    if(playerControl1->text() == "Disabled"){
        return;
    }
    QDir appDir(QCoreApplication::applicationDirPath());
    QString imageDir;
    
    QString colour = action->text();
    imageDir = getImagePath(colour+".jpg");
    emit changePlayerColour(1, action);
    playerImage1->setPixmap(QPixmap(imageDir));
    playerColour1->setText(colour);

}

void MiddlePage::changePlayerColour2(QAction *action){
    if(playerControl2->text() == "Disabled"){
        return;
    }
    QDir appDir(QCoreApplication::applicationDirPath());
    QString imageDir;
    
    QString colour = action->text();
    imageDir = getImagePath(colour+".jpg");
    emit changePlayerColour(2, action);
    playerImage2->setPixmap(QPixmap(imageDir));
    playerColour2->setText(colour);

}

void MiddlePage::changePlayerColour3(QAction *action){
    if(playerControl3->text() == "Disabled"){
        return;
    }
    QDir appDir(QCoreApplication::applicationDirPath());
    QString imageDir;
    
    QString colour = action->text();
    imageDir = getImagePath(colour+".jpg");
    emit changePlayerColour(3, action);
    playerImage3->setPixmap(QPixmap(imageDir));
    playerColour3->setText(colour);

}

void MiddlePage::changePlayerControl1(QAction *action){
    QString control = action->text();
    playerControl1->setText(control);
    if(control == "Enabled"){
        playerImage1->setPixmap(QPixmap(getImagePath("green.jpg")));
        playerColour1->setText("Green");
        playerName1->clear();
        playerName1->setReadOnly(false);
    }else if(control == "Disabled"){
        playerImage1->setPixmap(QPixmap(getImagePath("notEnabled.jpg")));
        playerColour1->setText("colour");
        playerName1->clear();
        playerName1->setReadOnly(true);
    }else if(control == "AI"){
        playerImage1->setPixmap(QPixmap(getImagePath("green.jpg")));
        playerColour1->setText("Green");
        playerName1->setText("AI");
        playerName1->setReadOnly(true);
        emit changePlayerName(1, "AI");
    }
    emit changePlayerController(1, action);
}

void MiddlePage::changePlayerControl2(QAction *action){
    QString control = action->text();
    playerControl2->setText(control);
    if(control == "Enabled"){
        playerImage2->setPixmap(QPixmap(getImagePath("green.jpg")));
        playerColour2->setText("Green");
        playerName2->setReadOnly(false);
    }else if(control == "Disabled"){
        playerImage2->setPixmap(QPixmap(getImagePath("notEnabled.jpg")));
        playerColour2->setText("colour");
        playerName2->setReadOnly(true);
    }else if(control == "AI"){
        playerImage2->setPixmap(QPixmap(getImagePath("green.jpg")));
        playerColour2->setText("Green");
        playerName2->setText("AI");
        playerName2->setReadOnly(true);
        emit changePlayerName(2, "AI");
    }
    emit changePlayerController(2, action);
}

void MiddlePage::changePlayerControl3(QAction *action){
    QString control = action->text();
    playerControl3->setText(control);
    if(control == "Enabled"){
        playerImage3->setPixmap(QPixmap(getImagePath("green.jpg")));
        playerColour3->setText("Green");
        playerName3->setReadOnly(false);
    }else if(control == "Disabled"){
        playerImage3->setPixmap(QPixmap(getImagePath("notEnabled.jpg")));
        playerColour3->setText("colour");
        playerName3->setReadOnly(true);
    }else if(control == "AI"){
        playerImage3->setPixmap(QPixmap(getImagePath("green.jpg")));
        playerColour3->setText("Green");
        playerName3->setText("AI");
        playerName3->setReadOnly(true);
        emit changePlayerName(3, "AI");
    }
    emit changePlayerController(3, action);
}

int MiddlePage::getPlayerNumber(){
    int playerNumber = 0;
    if(playerControl1->text() == "Enabled" || playerControl1->text() == "AI"){
        playerNumber++;
    }
    if(playerControl2->text() == "Enabled" || playerControl2->text() == "AI"){
        playerNumber++;
    }
    if(playerControl3->text() == "Enabled" || playerControl3->text() == "AI"){
        playerNumber++;
    }
    return playerNumber;
}

void MiddlePage::changeLanguage(QString language){
    if(language == "en"){
        this->player1->setText("Player 1:");
        this->player2->setText("Player 2:");
        this->player3->setText("Player 3:");
        this->startButton->setText("Start Game");
        this->exitButton->setText("Exit");

    }else if(language == "zh"){
        this->player1->setText("玩家1:");
        this->player2->setText("玩家2:");
        this->player3->setText("玩家3:");
        this->startButton->setText("开始游戏");
        this->exitButton->setText("退出游戏");
    }
}