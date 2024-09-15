#include "inifilemanager.h"

Inifilemanager::Inifilemanager() {}

int Inifilemanager::getDisplayScreen(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCREEN/Display").toInt();
    return settings.value("SCREEN/Display").toInt();
    //qDebug()<< settings.value("SCREEN/Display").toInt();
}

QString Inifilemanager::getManufacturerFromFile(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCREEN/Manufacturer").toString();
    return settings.value("SCREEN/Manufacturer").toString();

}

QString Inifilemanager::getModelFromFile(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCREEN/Model").toString();
    return settings.value("SCREEN/Model").toString();
}

QString Inifilemanager::getSerialNumberFromFile(){
    QSettings settings("Config/Setup.ini", QSettings::IniFormat);
    qDebug()<< settings.value("SCREEN/SerialNumber").toString();
    return settings.value("SCREEN/SerialNumber").toString();

}
