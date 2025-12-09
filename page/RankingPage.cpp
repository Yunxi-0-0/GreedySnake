#include "RankingPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QMessageBox>
#include <QCoreApplication>

RankingPage::RankingPage(QWidget *parent) : QWidget(parent){
    titleLabel = new QLabel("Ranking", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    table = new QTableWidget(this);
    table->setColumnCount(4);
    QStringList headers;
    headers << "Rank" << "Name" << "Score" << "Date";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QTableWidget::NoEditTriggers);
    table->setSelectionBehavior(QTableWidget::SelectRows);
    table->setSelectionMode(QTableWidget::SingleSelection);

    backButton = new QPushButton("Back", this);
    refreshButton = new QPushButton("Refresh", this);
    clearButton = new QPushButton("Clear", this);

    connect(backButton, &QPushButton::clicked, this, [this](){
        emit backButtonClicked();
    });
    connect(refreshButton, &QPushButton::clicked, this, &RankingPage::onRefreshClicked);
    connect(clearButton, &QPushButton::clicked, this, &RankingPage::onClearClicked);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(backButton, 0, Qt::AlignLeft);
    topLayout->addStretch();
    topLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    topLayout->addStretch();
    topLayout->addWidget(refreshButton, 0, Qt::AlignRight);
    topLayout->addWidget(clearButton, 0, Qt::AlignRight);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(table);
    setLayout(mainLayout);

    loadRankings();
}

QString RankingPage::rankingFilePath(){
    QString dir = QCoreApplication::applicationDirPath();
    return dir + "/rankings.txt";
}

void RankingPage::loadRankings(){
    table->setRowCount(0);
    QFile file(rankingFilePath());
    if(!file.exists()){
        // show placeholder rows
        table->setRowCount(5);
        for(int i=0;i<5;i++){
            table->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
            table->setItem(i, 1, new QTableWidgetItem("--"));
            table->setItem(i, 2, new QTableWidgetItem("0"));
            table->setItem(i, 3, new QTableWidgetItem("--"));
        }
        return;
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&file);
    QList<QList<QString>> rows;
    while(!in.atEnd()){
        QString line = in.readLine().trimmed();
        if(line.isEmpty()) continue;
        // expect CSV: name,score,datetime
        QStringList parts = line.split(',');
        if(parts.size() < 2) continue;
        QString name = parts.value(0).trimmed();
        QString score = parts.value(1).trimmed();
        QString date = parts.value(2).trimmed();
        rows.append({name, score, date});
    }
    file.close();

    // sort by score descending
    std::sort(rows.begin(), rows.end(), [](const QList<QString>& a, const QList<QString>& b){
        bool ok1, ok2;
        int s1 = a.value(1).toInt(&ok1);
        int s2 = b.value(1).toInt(&ok2);
        if(!ok1) s1 = 0;
        if(!ok2) s2 = 0;
        return s1 > s2;
    });

    int r = rows.size();
    table->setRowCount(r);
    for(int i=0;i<r;i++){
        table->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        table->setItem(i, 1, new QTableWidgetItem(rows[i].value(0)));
        table->setItem(i, 2, new QTableWidgetItem(rows[i].value(1)));
        table->setItem(i, 3, new QTableWidgetItem(rows[i].value(2)));
    }
}

void RankingPage::onRefreshClicked(){
    loadRankings();
}

void RankingPage::onClearClicked(){
    QString path = rankingFilePath();
    QFile file(path);
    if(file.exists()){
        file.remove();
    }
    loadRankings();
}

void RankingPage::saveRankings(){
    // Not used by UI currently, implemented for completeness
    QFile file(rankingFilePath());
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    int rows = table->rowCount();
    for(int i=0;i<rows;i++){
        QString name = table->item(i,1) ? table->item(i,1)->text() : "";
        QString score = table->item(i,2) ? table->item(i,2)->text() : "0";
        QString date = table->item(i,3) ? table->item(i,3)->text() : QDateTime::currentDateTime().toString();
        out << name << "," << score << "," << date << "\n";
    }
    file.close();
}