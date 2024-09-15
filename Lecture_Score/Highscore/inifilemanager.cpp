#include "inifilemanager.h"

IniFileManager::IniFileManager() {}


QString IniFileManager::getPasswordFromFile(){
    QSettings sett("Config/Setup.ini",QSettings::IniFormat);
    //qDebug()<<sett.value("USER/Password").toString();
    return sett.value("USER/Password").toString();

}

QString IniFileManager::getUsernameFromFile(){
    QSettings sett("Config/Setup.ini",QSettings::IniFormat);
    return sett.value("USER/Username").toString();
}

QString IniFileManager::getPinemhiPathFromFile(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    return settings.value("PATH/Leaderboard").toString();
    //qDebug()<< settings.value("PATH/Leaderboard").toString();

}

int IniFileManager::getDisplayScreen(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCREEN/Display").toInt();
    return settings.value("SCREEN/Display").toInt();
    //qDebug()<< settings.value("SCREEN/Display").toInt();
}

QString IniFileManager::getResolution(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCALE/Size_screen").toString();
    return settings.value("SCALE/Size_screen").toString();
}

QString IniFileManager::getManufacturerFromFile(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCREEN/Manufacturer").toString();
    return settings.value("SCREEN/Manufacturer").toString();

}

QString IniFileManager::getModelFromFile(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCREEN/Model").toString();
    return settings.value("SCREEN/Model").toString();
}

QString IniFileManager::getSerialNumberFromFile(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCREEN/SerialNumber").toString();
    return settings.value("SCREEN/SerialNumber").toString();

}


QString IniFileManager::getKeyTable(const QString &input){
    QSettings settings("Config/rom.ini", QSettings::IniFormat);
    QStringList keys = settings.allKeys();
    /*
    for (const QString &key : keys) {
        qDebug() << "Key:" << key << "Value:" << settings.value(key).toString();
    }*/
    qDebug()<<input;
    qDebug()<<"getKeyTable" << settings.value("romfind/"+input).toString();
    return settings.value("romfind/"+input).toString();
}

QString IniFileManager::getTitle(const QString &input){
    QSettings settings("Config/rom.ini", QSettings::IniFormat);
    /*
    QStringList keys = settings.allKeys();

    for (const QString &key : keys) {
        qDebug() << "Key:" << key << "Value:" << settings.value(key).toString();
    }
    */
    qDebug()<<"getTitle" << settings.value("romfind/"+input).toString();
    return settings.value("romfind/"+input).toString();
}
