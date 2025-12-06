#include "tools.h"
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