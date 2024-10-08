#include "thread.h"
#include <QtCore>

Thread::Thread(const QString& processName, QString user, QString title, QString pinemhiPATH, QString nvram)
    :  m_user(user), m_processName(processName), m_title(title),m_pinemhiPATH(pinemhiPATH),m_NVRAM(nvram)
{}


void Thread::run()
{   //tant qu'il n'est pas interrompu (tant que la partie n'est pas finis)
    while (!isInterruptionRequested())
    {

        QProcess process;
        //Processus de VisualPinballX
        process.start("tasklist", QStringList() << "/FI" << "IMAGENAME eq " + m_processName);
        //Si VisualPinballX est fermé alors.. (Si la partie est terminé alors..)
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



                //écriture dans Score/Score.ini du chemin pour lire le fichier score de PinemHi + le titre de la table + username
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



                // Lancement de Score.exe afin d'excuter le script pour enregistrer les scores
                QString exeScorePATH="Score.exe";
                //Execution de front.exe apres fermuture de la table
                //QString exePath = "Front.exe";
                QString exePath = QCoreApplication::applicationDirPath() + "/Front.exe";

                //Lancement de Score.exe + Front.exe
                QProcess *processScore = new QProcess();
                QProcess *processFront = new QProcess();


                processScore->start(exeScorePATH);
                processFront->start(exePath);

                //Temps d'attente pour la fermeture de Highscore.exe
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





