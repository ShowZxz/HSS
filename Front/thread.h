#ifndef THREAD_H
#define THREAD_H

#include "qdebug.h"
#include <QThread>
#include <QtCore>



class Thread : public QThread
{
public:
    Thread(const QString& processName);
    void run();
    Thread();


private:
    QString m_processName;

signals:
    void requestQuit();

};

#endif // THREAD_H
