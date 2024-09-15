#ifndef INIFILEMANAGER_H
#define INIFILEMANAGER_H

#include <QString>
#include <QSettings>

class Inifilemanager
{
public:
    Inifilemanager();
    QString getUsernameFromFile();
    QString getTitleFromFile();
    QString getPathFromFile();
};

#endif // INIFILEMANAGER_H
