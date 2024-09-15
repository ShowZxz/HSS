#include "manager.h"
#include "qdebug.h"

Manager::Manager() {}



long long Manager::recupererMeilleurScore(const QString &file){
    QFile fichier(file);
    int meilleurScore = 0;
    int ligneActuelle = 0;

    if (fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichier);
        QString line;
        QString gameTitle;
        qDebug() <<"FILEEEEE OPEEEEEEEEEEEEEEEEEEEENNNN";

        // Recherche du highscore et de l'utilisateur à la ligne 7
        int lineNumber = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            //qDebug()<<"LIGNE"<<line;

            lineNumber++;
            //qDebug()<<lineNumber;
            if (lineNumber == 3) {
                int start = line.indexOf("<<<") + 3;
                int end = line.lastIndexOf(">>>");

                if (start != -1 && end != -1 && start < end) {
                    gameTitle = line.mid(start, end - start).trimmed();
                    setTitleTable(gameTitle);
                    qDebug() << "Game Title:" << gameTitle;
                }
            }

            if (lineNumber == 7) {
                //qDebug()<<"LIGNE"<<line;
                QStringList parts = line.split(" ", Qt::SkipEmptyParts);
                //qDebug()<<parts;

                if (parts.size() >= 5) {

                    QString highscore = parts.at(1);

                    if (highscore.isEmpty()){
                        qDebug() << "SCORE VIDE";
                        return meilleurScore;

                    }
                    QString tempHighscore = highscore;
                    tempHighscore.replace(".","");
                    meilleurScore = tempHighscore.toLongLong();
                    qDebug() << "THREAD ###################################### Highscore:" << highscore <<tempHighscore <<meilleurScore;
                    return meilleurScore;

                }

            }


            fichier.close();
        }

    }
    else {

        qDebug() << "Erreur lors de l'ouverture du fichier";
    }

    return meilleurScore;
}

void Manager::setByDefault(){
    QSettings settings("Score/Info.ini", QSettings::IniFormat);
    settings.beginGroup("Info");
    settings.setValue("Path", "");
    settings.setValue("Table", "");
    settings.endGroup();
}
