#ifndef INIFILEMANAGER_H
#define INIFILEMANAGER_H

#include <QSettings>

class Inifilemanager
{
public:
    Inifilemanager();
    int getDisplayScreen();
    QString getManufacturerFromFile();
    QString getModelFromFile();
    QString getSerialNumberFromFile();
};

#endif // INIFILEMANAGER_H
