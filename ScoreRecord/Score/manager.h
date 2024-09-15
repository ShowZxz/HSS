#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QSettings>

class Manager
{
public:
    Manager();


    void setUserPinemhiScore(long long userPinemhiScore){
        this->userPinemhiScore = userPinemhiScore;
    }

    void setTitleTable(QString title){
        this->title = title;
    }
    void setByDefault();
    QString getTitleTable(){return title;};

    long long getUserPinemhiScore(){return userPinemhiScore;}

    QString formatStringWithSpaces(const QString &input);
    long long recupererMeilleurScore(const QString &file);




private:

    long long userPinemhiScore = 0;
    QString title ="";

};

#endif // MANAGER_H
