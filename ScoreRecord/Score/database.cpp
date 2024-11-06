#include "database.h"
#include "qdebug.h"

Database::Database() {
    openDatabase();
}
// Connexion BDD
bool Database::openDatabase(){
	struct databaseInfo
    {
        QByteArray host="MTk0LjE2NC42My41Nw==";
        QByteArray user="c3Bpbm5lcl9oc191c2Vy";
        QByteArray password="bmRwOWV4ZEBNQkcxdnVmLWNkag==";
        QByteArray dbname="c3Bpbm5lcl9oaWdoc2NvcmVfZGI=";

    }Infodb;
	QByteArray decodedHost=QByteArray::fromBase64(Infodb.host);
    QByteArray decodedPassword = QByteArray::fromBase64(Infodb.password);
    QByteArray decodedUser = QByteArray::fromBase64(Infodb.user);
    QByteArray decodedDbname = QByteArray::fromBase64(Infodb.dbname);
	
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(decodedHost);
    db.setPort(3306);
    db.setDatabaseName(decodedDbname);
    db.setUserName(decodedUser);
    db.setPassword(decodedPassword );
    

    if (db.open()){
        return true;
    } else {
        qDebug() <<"Erreur de connexion a la BDD "<< db.lastError().text();
        return false;
    }

}
// Fermeture de la BDD
void Database::closeDatabase(){
    db.close();
}

//Fonction pour vérifier si le jeu existe dans la BDD
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
//Fonction Pour enregister le score dans la BDD
void Database::recordDatabase(const QString &table, const QString &username, const long long &score){
    QString time_format = "yyyy-MM-dd hh:mm:ss";
    QString _datetime=QDateTime::currentDateTime().toString(time_format);
    //Vérification des données necessaire pour l'enregistrement
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
            //Si le score sélectionner dans la BDD est inférieur au nouveau score alors on éffectue une mise a jour du score
            if (score > oldScore) {
                // Mettre à jour l'enregistrement au score existant
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
            // Insértion d'un nouvel enregistrement si l'ancien n'existe pas
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
