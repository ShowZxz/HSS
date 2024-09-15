#include "thread.h"
#include "qprocess.h"


Thread::Thread(const QString& processName)
    :  m_processName(processName)
{}

void Thread::run()
{
    while (!isInterruptionRequested()) {
        QProcess process;
        process.start("tasklist", QStringList() << "/FI" << "IMAGENAME eq " + m_processName);

        sleep(2);

        if (process.waitForFinished())
        {
            QByteArray output = process.readAllStandardOutput();

            QString outputStr(output);
            if (outputStr.contains(m_processName))
            {

                qDebug() << m_processName << "is running.";
            }
            else
            {
                qDebug() << m_processName << "is not running.";

                QCoreApplication::quit();
            }
        }
    }
}

