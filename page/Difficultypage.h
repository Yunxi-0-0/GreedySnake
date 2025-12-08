
#ifndef DIFFICULTYPAGE_H
#define DIFFICULTYPAGE_H

#include "qobject.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class DifficultyPage : public QWidget
{
    Q_OBJECT
public:
    DifficultyPage(QWidget *parent = nullptr);  // 不要 explicit
    void changeLanguage(QString language);
    QPushButton *btnEasy;
    QPushButton *btnNormal;
    QPushButton *btnHard ;
    QPushButton *btnBack;
    QLabel *label;

signals:
    void difficultySelected(int level);
    void backButtonClicked();
    void startGame();
};

#endif // DIFFICULTYPAGE_H
