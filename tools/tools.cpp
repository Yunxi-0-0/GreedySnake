#include "tools.h"
#include "qdir.h"
#include "qmessagebox.h"
#include "qobject.h"
#include <QDebug>

QString getImagePath(const QString& imageName)
{
    QDir appDir(QCoreApplication::applicationDirPath());
    appDir.cdUp();
    if(appDir.dirName()!="GreedySnake"){
        appDir.cdUp();
    }
    QString imageDir = appDir.filePath("image/"+imageName);
    return imageDir;
}

QString getIconPath(const QString& iconName){
    QDir appDir(QCoreApplication::applicationDirPath());
    appDir.cdUp();
    if(appDir.dirName()!="GreedySnake"){
        appDir.cdUp();
    }
    QString iconDir = appDir.filePath(iconName);
    return iconDir;
}

QString getstylesheetPath(const QString& styleName){
    QDir appDir(QCoreApplication::applicationDirPath());
    appDir.cdUp();
    if(appDir.dirName()!="GreedySnake"){
        appDir.cdUp();
    }
    QString stylesheetDir = appDir.filePath("styles/"+styleName);
    return stylesheetDir;
}

QString getMusicPath(const QString& musicName){
    QDir appDir(QCoreApplication::applicationDirPath());
    appDir.cdUp();
    if(appDir.dirName()!="GreedySnake"){
        appDir.cdUp();
    }
    QString musicDir = appDir.filePath("music/"+musicName);
    if (!QFile::exists(musicDir)) {
        QMessageBox::warning(nullptr, "Music Not Found", "Music file not found.");
    }
    return musicDir;
}