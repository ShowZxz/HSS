#include "thread.h"
#include <QtCore>

Thread::Thread(const QString& processName, QString user, QString title, QString pinemhiPATH, QString nvram)
    :  m_user(user), m_processName(processName), m_title(title),m_pinemhiPATH(pinemhiPATH),m_NVRAM(nvram)
{}


void Thread::run()
{
    while (!isInterruptionRequested())
    {

        QProcess process;
        process.start("tasklist", QStringList() << "/FI" << "IMAGENAME eq " + m_processName);

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
                qDebug() <<"THREAD ARG : "<<m_user<<m_processName<<m_title<<m_pinemhiPATH<<m_NVRAM;

                //######################################################## INI FILE#####################################################################################################

                qDebug() << "THREAD ###################################### INI FILE ##############################################################################" ;



                //transfert du score
                if ( !m_title.isEmpty() && !m_user.isEmpty() && !m_NVRAM.isEmpty() && !m_NVRAM.isEmpty() ){
                    QString scorePATH = m_pinemhiPATH+m_NVRAM;
                    qDebug() <<scorePATH;
                    QSettings settings("Score/Info.ini", QSettings::IniFormat);
                    settings.beginGroup("Info");
                    settings.setValue("Path", scorePATH);
                    settings.setValue("Table", m_title);
                    settings.setValue("Username", m_user);
                    settings.endGroup();


                }
                //else {
                    // Nom du jeu + token original
                    qDebug() <<"ELSE";
                    //QString tramError = "Cannot Store the data collected  Verify the pinemhi path";
                    //QMessageBox::critical(nullptr, "Error",tramError);
                    //sleep(2);
                    //QCoreApplication::quit();

                //}



                // lancement de l'enregistrement
                QString exeScorePATH="Score.exe";
                //Execution du front apres fermuture de la table
                //QString exePath = "Front.exe";
                QString exePath = QCoreApplication::applicationDirPath() + "/Front.exe";
                QProcess *processScore = new QProcess();
                QProcess *processFront = new QProcess();


                processScore->start(exeScorePATH);
                processFront->start(exePath);

                sleep(3);


                qDebug()<<"Leaving........";
                QCoreApplication::quit();
                qDebug()<<"Leaving ???........";



                break;
            }
        }
        else
        {
            qDebug() << "Error running tasklist.";
        }



    }

}





