#include "thread.h"
#include "qprocess.h"


Thread::Thread(const QString& processName)
    :  m_processName(processName)
{}

void Thread::run()
{

    //tant qu'il n'est pas interrompu
    while (!isInterruptionRequested()) {
        QProcess process;
        process.start("tasklist", QStringList() << "/FI" << "IMAGENAME eq " + m_processName);

        sleep(2);
        //Processus de PinupMenu.exe
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

                //Fermeture quand PinupMenu.exe est fermé
                QCoreApplication::quit();
            }
        }
    }
}

