#include "inifilemanager.h"

Inifilemanager::Inifilemanager() {}

QString Inifilemanager::getTitleFromFile(){
    QSettings sett("Score/Info.ini",QSettings::IniFormat);

    return sett.value("Info/Table").toString();

}

QString Inifilemanager::getUsernameFromFile(){
    QSettings sett("Score/Info.ini",QSettings::IniFormat);
    return sett.value("Info/Username").toString();
}

QString Inifilemanager::getPathFromFile(){
    QSettings sett("Score/Info.ini",QSettings::IniFormat);
    return sett.value("Info/Path").toString();
    //qDebug()<< settings.value("PATH/Leaderboard").toString();

}
