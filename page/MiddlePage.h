#pragma once

#include "qboxlayout.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qmenu.h"
#include "qobject.h"
#include "qtoolbutton.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QToolButton>
#include <QMenu>
#include <QAction>

class MiddlePage : public QWidget
{
    Q_OBJECT
public:
    explicit MiddlePage(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;

    QHBoxLayout *playerLayout;
    QVBoxLayout *playerLayout1;
    QVBoxLayout *playerLayout2;
    QVBoxLayout *playerLayout3;

    QLabel *player1;
    QLabel *player2;
    QLabel *player3;

    QLabel *playerImage1;
    QLabel *playerImage2;
    QLabel *playerImage3;

    QMenu *colourMenu1;
    QToolButton *playerColour1;
    QMenu *colourMenu2;
    QToolButton *playerColour2;
    QMenu *colourMenu3;
    QToolButton *playerColour3;

    QLineEdit *playerName1;
    QLineEdit *playerName2;
    QLineEdit *playerName3;

    QMenu *controlMenu1;
    QToolButton *playerControl1;
    QMenu *controlMenu2;
    QToolButton *playerControl2;
    QMenu *controlMenu3;
    QToolButton *playerControl3;


    QPushButton *startButton;
    QPushButton *exitButton;

    int getPlayerNumber();

    void initUI();
    void initConnections();


signals:
    void startGame();
    void exitGame();
    void changePlayerColour(int player, QAction *action);
    void changePlayerController(int player, QAction *action);
    void changePlayerName(int player, QString name);

public slots:
    void changePlayerColour1(QAction *action);
    void changePlayerColour2(QAction *action);
    void changePlayerColour3(QAction *action);
    void changePlayerControl1(QAction *action);
    void changePlayerControl2(QAction *action);
    void changePlayerControl3(QAction *action);
    void changeLanguage(QString language);

    
};