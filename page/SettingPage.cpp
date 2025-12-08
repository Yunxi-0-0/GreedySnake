#include "SettingPage.h"
#include "qnamespace.h"
#include "qtmetamacros.h"

SettingPage::SettingPage(QTranslator *translator, QWidget *parent)
    : QWidget(parent), m_translator(translator) {
    // 设置窗口属性
    setWindowTitle(tr("setting"));

    // 初始化控件
    backButton = new QPushButton(tr("Back"), this);

    volumeLabel = new QLabel("Volume", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    langLabel = new QLabel("Language", this);
    langCombo = new QComboBox(this);
    themeLabel = new QLabel(tr("Theme"), this);
    themeCombo = new QComboBox(this);

    volumeLabel->setFixedSize(300, 40);
    volumeSlider->setFixedSize(300, 40);
    langCombo->setFixedSize(300, 40);
    langLabel->setFixedSize(300, 40);
    themeCombo->setFixedSize(300, 40);
    themeLabel->setFixedSize(300, 40);


    // 配置音量滑块
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50); // 默认音量50%

    // 配置语言下拉框（支持中、英、日、韩）
    langCombo->addItem(tr("English"), "en");
    langCombo->addItem(tr("中文"), "zh");

    themeCombo->addItem("light","light");
    themeCombo->addItem("dark","dark");

    // 布局管理
    QVBoxLayout *layout = new QVBoxLayout(this);

    // layout->addWidget(langCombo,0, Qt::AlignCenter);
    // layout->addSpacing(20);
    // layout->addWidget(volumeSlider, 0, Qt::AlignCenter);
    // layout->addStretch();
    // layout->addWidget(backButton, 0, Qt::AlignCenter);
    layout->addWidget(langLabel, 0, Qt::AlignCenter);
    layout->addWidget(langCombo, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(volumeLabel, 0, Qt::AlignCenter);
    layout->addWidget(volumeSlider, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(themeLabel, 0, Qt::AlignCenter);
    layout->addWidget(themeCombo, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(backButton, 0, Qt::AlignCenter);



    // 连接信号槽
    connect(backButton, &QPushButton::clicked, this, &SettingPage::onBackButtonClicked);
    connect(volumeSlider, &QSlider::valueChanged, this, &SettingPage::volumeChanged);
    connect(langCombo, &QComboBox::currentIndexChanged, this, &SettingPage::onLangComboChanged);
    connect(this, &SettingPage::languageChanged, this, &SettingPage::setLanguage);
    connect(volumeSlider, &QSlider::valueChanged, [=](int value) {
        emit volumeChanged(value/100.0);
    });
    connect(themeCombo, &QComboBox::currentIndexChanged, [=](int index) {
        QString theme = themeCombo->itemData(index).toString();
        emit themeChanged(theme);
    });
}

// 返回按钮点击：发射返回信号
void SettingPage::onBackButtonClicked() {
    emit backButtonClicked();
}

// 语言选择变化：发射语言变化信号
void SettingPage::onLangComboChanged(int index) {
    QString lang = langCombo->itemData(index).toString();
    setLanguage(lang);
    emit languageChanged(lang);
}

void SettingPage::setLanguage(const QString &lang) {
    if(lang == "zh"){
        backButton->setText(tr("返回主界面"));
        langLabel->setText(tr("语言"));
        volumeLabel->setText(tr("音量"));
        themeLabel->setText(tr("主题"));
        themeCombo->setItemText(0,tr("浅色"));
        themeCombo->setItemText(1,tr("深色"));
        this->setWindowTitle(tr("设置"));

    }else if(lang == "en"){
        backButton->setText(tr("Back"));
        langLabel->setText(tr("Language"));
        volumeLabel->setText(tr("Volume"));
        themeLabel->setText(tr("Theme"));
        themeCombo->setItemText(0,tr("light"));
        themeCombo->setItemText(1,tr("dark"));
        this->setWindowTitle(tr("Setting"));
    }
}