#pragma once
#include "qcombobox.h"
#include "qlabel.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QTranslator>

class SettingPage : public QWidget{
    Q_OBJECT
public:
    // 构造函数接收翻译器指针（用于语言切换）和父窗口
    SettingPage(QTranslator *translator, QWidget *parent = nullptr);

private:
    QPushButton *backButton;
    QSlider *volumeSlider;       // 音量控制滑块
    QLabel *volumeLabel;         // 音量显示标签
    QComboBox *langCombo;        // 语言选择下拉框
    QLabel *langLabel;           // 语言显示标签
    QTranslator *m_translator;   // 翻译器指针（关联主窗口）
    QComboBox *themeCombo;       // 主题选择下拉框
    QLabel *themeLabel;          // 主题显示标签
    void setLanguage(const QString &lang); // 设置语言

signals:
    void backButtonClicked();                     // 返回按钮信号
    void volumeChanged(double volume);               // 音量变化信号
    void languageChanged(const QString &lang);    // 语言变化信号
    void themeChanged(const QString &theme);     // 主题变化信号

private slots:
    void onBackButtonClicked();   // 返回按钮点击槽函数
    void onLangComboChanged(int index); // 语言选择变化槽函数
};

// 实现文件（可直接写在头文件中，或单独创建 .cpp 文件）
#include <QApplication>


