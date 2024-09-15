#ifndef INIFILEMANAGER_H
#define INIFILEMANAGER_H

#include <QString>
#include <QSettings>
class IniFileManager
{
public:
    IniFileManager();
    QString getUsernameFromFile();
    QString getPasswordFromFile();
    QString getPinemhiPathFromFile();
    QString getManufacturerFromFile();
    QString getModelFromFile();
    QString getSerialNumberFromFile();
    QString getResolution();
    int getDisplayScreen();
    QString getKeyTable(const QString &input);
    QString getTitle(const QString &input);


};

#endif // INIFILEMANAGER_H
