#pragma once
#include "qtmetamacros.h"
#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>

class RankingPage : public QWidget
{
    Q_OBJECT
public:
    RankingPage(QWidget *parent = nullptr);
private:
    QLabel *titleLabel;
    QTableWidget *table;
    QPushButton *backButton;
    QPushButton *refreshButton;
    QPushButton *clearButton;
    void loadRankings();
    void saveRankings();
    QString rankingFilePath();
signals:
    void backButtonClicked();
public slots:
    void onRefreshClicked();
    void onClearClicked();
};