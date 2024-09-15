#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include <windows.h>
#include <QKeyEvent>
#include <thread>
#include <conio.h>

class Manager
{
public:
    Manager();

    void setfrontPosUser(QString frontPosUser){
        this->frontPosUser =frontPosUser;
    }
    void setbehindPosUser(QString behindPosUser){
        this->behindPosUser =behindPosUser;
    }
    void setfrontPosScore(QString frontPosScore){
        this->frontPosScore =frontPosScore;
    }
    void setbehindPosScore(QString behindPosScore){
        this->behindPosScore =behindPosScore;
    }
    void setworldPosScore(QString worldPosScore){
        this->worldPosScore =worldPosScore;
    }
    void setworldPosUser(QString worldPosUser){
        this->worldPosUser =worldPosUser;
    }
    void setUserPinemhiScore(long long userPinemhiScore){
        this->userPinemhiScore = userPinemhiScore;
    }

    QString getfrontPosUser(){return frontPosUser;}
    QString getbehindPosUser(){return behindPosUser;}
    QString getworldPosUser(){return worldPosUser;}

    QString getworldPosScore(){return worldPosScore;}
    QString getfrontPosScore(){return frontPosScore;}
    QString getbehindPosScore(){return behindPosScore;}
    long long getUserPinemhiScore(){return userPinemhiScore;}

    QString formatStringWithSpaces(const QString &input);
    QString setZeroToOne(const QString &input);




private:
    QString frontPosUser;
    QString frontPosScore;
    QString behindPosUser;
    QString behindPosScore;
    QString worldPosScore;
    QString worldPosUser;
    long long userPinemhiScore = 0;

};

#endif // MANAGER_H
