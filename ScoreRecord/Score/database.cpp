#include "database.h"
#include "qdebug.h"

Database::Database() {
    openDatabase();
}

bool Database::openDatabase(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("194.164.63.57");
    db.setPort(3306);
    db.setDatabaseName("spinner_highscore_db");
    db.setUserName("spinner_hs_user");
    db.setPassword("ndp9exd@MBG1vuf-cdj");

    if (db.open()){
        return true;
    } else {
        qDebug() <<"Erreur de connexion a la BDD "<< db.lastError().text();
        return false;
    }

}

void Database::closeDatabase(){
    db.close();
}

bool Database::existGameDatabase(const QString &table){
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM jeux WHERE Nom_jeu = :Title");
    query.bindValue(":Title",table);

    if (!query.exec()){
        qDebug()<< "ERREUR lors de la verification de l'existence de la table"<<query.lastError();
        return false;
    }

    if (query.next()){
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

void Database::recordDatabase(const QString &table, const QString &username, const long long &score){
    QString time_format = "yyyy-MM-dd hh:mm:ss";
    QString _datetime=QDateTime::currentDateTime().toString(time_format);

    if (!table.isEmpty() && !username.isEmpty() && score != 0){

        QString selectQueryStr = QString("SELECT s.Score "
                                         "FROM scores s "
                                         "JOIN utilisateurs u ON s.ID_utilisateur = u.ID_utilisateur "
                                         "JOIN jeux j ON s.ID_jeu = j.ID_jeu "
                                         "WHERE u.Pseudo = :User AND j.Nom_jeu = :Title;");

        QSqlQuery selectQuery;
        selectQuery.prepare(selectQueryStr);
        selectQuery.bindValue(":User", username);
        selectQuery.bindValue(":Title", table);

        if (selectQuery.exec() && selectQuery.next()) {
            qlonglong oldScore = selectQuery.value(0).toLongLong();
            qDebug()<< "Old Score = " <<oldScore<< "New Score = "<<score;

            if (score > oldScore) {
                // Mettre à jour l'enregistrement existant
                QString updateQueryStr = QString("UPDATE scores s "
                                                 "JOIN utilisateurs u ON s.ID_utilisateur = u.ID_utilisateur "
                                                 "JOIN jeux j ON s.ID_jeu = j.ID_jeu "
                                                 "SET s.Score = :Score, s.Date_enregistrement = :Datetime "
                                                 "WHERE u.Pseudo = :User AND j.Nom_jeu = :Title;");
                QSqlQuery updateQuery;
                updateQuery.prepare(updateQueryStr);
                updateQuery.bindValue(":Score", score);
                updateQuery.bindValue(":Datetime", _datetime);
                updateQuery.bindValue(":User", username);
                updateQuery.bindValue(":Title", table);
                qDebug() <<" ###################################################MISE A JOUR OK THREAD #####################################################################";

                if (!updateQuery.exec()) {
                    qDebug() << updateQuery.lastError() << "Erreur lors de la mise à jour de l'enregistrement";
                }
            }
        } else {
            // Insérer un nouvel enregistrement si l'ancien n'existe pas
            QString insertQueryStr = QString("INSERT INTO scores (ID_utilisateur, ID_jeu, Score, Date_enregistrement) "
                                             "VALUES ( "
                                             "(SELECT ID_utilisateur FROM utilisateurs WHERE Pseudo = :User), "
                                             "(SELECT ID_jeu FROM jeux WHERE Nom_jeu = :Title), :Score, :Datetime )");

            QSqlQuery insertQuery;
            insertQuery.prepare(insertQueryStr);
            insertQuery.bindValue(":User", username);
            insertQuery.bindValue(":Title", table);
            insertQuery.bindValue(":Score", score);
            insertQuery.bindValue(":Datetime", _datetime);
            qDebug() <<"################################### NOUVEL INSERTION THREAD #################################################";

            if (!insertQuery.exec()) {
                qDebug() << insertQuery.lastError() << "Erreur lors de l'insertion d'un nouvel enregistrement";
            }
        }

    } else{
        qDebug() <<"ERROR################################### SCORE VIDE OU USER OU GAMEFULLNAME #################################################";
    }

}
