#ifndef THREAD_H
#define THREAD_H

#include "manager.h"
#include <QThread>
#include <QProcess>


class Thread : public QThread
{
public:
    Thread(const QString& processName,QString user,QString title,QString pinemhiPATH,QString nvram);
    void run();
    Thread();


private:



    Manager manager;

    QString m_user;
    QString m_processName;
    QString m_title;
    QString m_pinemhiPATH;
    QString m_NVRAM;

};

#endif // THREAD_H
