#include "database.h"



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

QList<LoginUser> Database::getLoginUser(const QString &pseudo, const QString &code) {
    QList<LoginUser> result;
    qDebug() << ":Pseudo =" << pseudo;
    qDebug() << ":Code =" << code;
    if (!db.open()) {
        qWarning() << "Erreur lors de l'ouverture de la base de données #getLoginUser# :" << db.lastError().text();
        // Lancer une exception ou signaler une erreur appropriée ici si nécessaire
        return result;
    }

    qDebug() << "######################################## Ouverture BDD getLoginUser. ###################################################";

    QString queryStr = "SELECT Pseudo, Code FROM utilisateurs WHERE Pseudo = :Pseudo AND Code = :Code;";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":Pseudo", pseudo);
    query.bindValue(":Code", code);

    if (!query.exec()) {
        qWarning() << "Erreur lors de l'exécution de la requête getLoginUser :" << query.lastError().text();
        // Lancer une exception ou signaler une erreur appropriée ici si nécessaire
        return result;
    }

    if (query.next()) {
        qDebug() << "Query exe getLoginUser.";

        // Debug des valeurs liées
        qDebug() << "Pseudo lié :" << query.boundValue(":Pseudo").toString();
        qDebug() << "Code lié :" << query.boundValue(":Code").toString();

        LoginUser loginUser;
        loginUser.pseudo = query.value(0).toString();
        loginUser.code = query.value(1).toString();

        result.append(loginUser);
        qDebug() << "######################################## FIN + execution BDD getLoginUser. ###################################################";
    } else {
        qDebug() << "######################################## PAS D'enregistrement avec ces valeurs BDD getLoginUser. ###################################################";
    }
    db.close();
    return result;
}


//####################################################################################### USER INFO QUERY ##########################################################################################
// Requête pour le meilleur score de l'utilisateur
QString Database::getHighscoreFromDatabase(QString username, QString title) {
    qDebug() << ":Pseudo =" << username;
    qDebug() << ":Title =" << title;

    if (!db.open()) {
        qDebug() << "Impossible d'ouvrir la base de données. getNewHighscore";
        return "Database connection error";
    } else {
        qDebug() << "######################################## Ouverture BDD getHighscoreFromDatabase. ###################################################";
    }


    QSqlQuery query;
    query.prepare("SELECT u.Pseudo AS Joueur, s.Score AS Meilleur_Score FROM scores s JOIN utilisateurs u ON s.ID_utilisateur = u.ID_utilisateur JOIN jeux j ON s.ID_jeu = j.ID_jeu WHERE j.Nom_jeu = :title AND u.Pseudo = :userName ORDER BY s.Score DESC LIMIT 1;");
    query.bindValue(":title", title);
    query.bindValue(":userName", username);


    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError() << "getHighscoreFromDatabase";
        return "Query execution error";
    }


    if (query.next()) {
        QString bestScore = query.value("Meilleur_Score").toString();
        qDebug() << "######################################## FIN + execution BDD getHighscoreFromDatabase. ###################################################";
        db.close();
        return bestScore;
    } else {
        qDebug() << "Aucun meilleur score trouvé pour l'utilisateur : " << username << " et le jeu : " << title;
        return "";
    }


    //close bdd maybe

}

// Request for user rank
QString Database::getInfoRank(const QString &user, const QString &title){
    QString result;
    if (!db.open()) {
        qDebug() << "Erreur lors de l'ouverture de la base de données"; return result;
    }

    qDebug() << "######################################## Ouverture BDD getInfoRank. ###################################################";

    QString queryStr = QString("SELECT s.Score AS Score,(SELECT COUNT(*) FROM scores s2 JOIN utilisateurs u ON s2.ID_utilisateur = u.ID_utilisateur JOIN jeux j ON s2.ID_jeu = j.ID_jeu WHERE j.Nom_jeu = '%1' AND s2.Score > s.Score) + 1 AS Rank FROM scores s JOIN utilisateurs u ON s.ID_utilisateur = u.ID_utilisateur JOIN jeux j ON s.ID_jeu = j.ID_jeu WHERE j.Nom_jeu = '%1' AND u.Pseudo = '%2';").arg(title).arg(user);


    QSqlQuery query;

    if (!query.exec(queryStr)) {
        qDebug() << "Erreur lors de l'exécution de la requête : " << query.lastError();

        return result;
    }

    if (query.next()) {
        QString score = query.value("score").toString();
        int rank = query.value("Rank").toInt();

        result = "Meilleur score de l'utilisateur " + user + " pour le titre " + title + " : " + score +
                 "\nClassement : #" + QString::number(rank);
        qDebug() << result;
        qDebug() << "######################################## FIN + execution BDD getInfoRank. ###################################################";
    }

    // Fermer la connexion à la base de données

    db.close();
    return result;
}

// Request for Top 1 info
QList<ScoreInfoTop> Database::getWorldHighscore(const QString &title){
    QList<ScoreInfoTop> worldScore;



    // Vérifier la connexion à la base de données
    if (!db.open()) {
        qDebug() << "Impossible d'ouvrir la base de données. getWorldScoreInfo";
        return worldScore;
    } else {
        qDebug() << "######################################## Ouverture BDD getWorldHighscore ###################################################";
    }

    // Préparer la requête SQL avec des paramètres liés
    QSqlQuery query;
    query.prepare("SELECT u.Pseudo AS User, s.Score "
                  "FROM scores s "
                  "JOIN utilisateurs u ON s.ID_utilisateur = u.ID_utilisateur "
                  "JOIN jeux j ON s.ID_jeu = j.ID_jeu "
                  "WHERE j.Nom_jeu = :title AND s.Score = (SELECT MAX(s2.Score) "
                  "FROM scores s2 "
                  "JOIN jeux j2 ON s2.ID_jeu = j2.ID_jeu "
                  "WHERE j2.Nom_jeu = :title2);");
    query.bindValue(":title", title);
    query.bindValue(":title2", title);

    // Exécuter la requête
    if (!query.exec()) {
        qDebug() << query.lastError() << "Erreur lors de l'exécution de la requête getWorldScoreInfo";
        return worldScore;
    }

    // Récupérer les résultats
    while (query.next()) {
        ScoreInfoTop scoreInfo;
        scoreInfo.username = query.value("User").toString();
        scoreInfo.score = query.value("Score").toLongLong();
        worldScore.append(scoreInfo);
        qDebug() <<scoreInfo.username<<scoreInfo.score;
        qDebug() << "######################################## FIN + execution BDD getWorldHighscore ###################################################";
    }

    // Fermer la connexion à la base de données (à placer dans une méthode séparée)
    db.close();

    return worldScore;


}
// Requête de pour la personne devant l'utilisateur
QList<ScoreInfoTop> Database::getTopScoresInFrontUser(const QString &title, const QString &user) {
    QList<ScoreInfoTop> topScores;

    qDebug() << title<<user;

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données getTopScoresInFronUse";
        return topScores;
    } else{
        qDebug() << "######################################## Ouverture BDD getTopScoresInFrontUser ###################################################";
    }

    QString queryStr = QString("WITH Classement AS ( "
                               "    SELECT "
                               "        u.Pseudo, "
                               "        s.Score, "
                               "        j.Nom_jeu, "
                               "        ROW_NUMBER() OVER (PARTITION BY j.Nom_jeu ORDER BY s.Score DESC) AS Classement "
                               "    FROM scores s "
                               "    JOIN utilisateurs u ON s.ID_utilisateur = u.ID_utilisateur "
                               "    JOIN jeux j ON s.ID_jeu = j.ID_jeu "
                               "    WHERE j.Nom_jeu = '%1' "
                               ") "
                               "SELECT "
                               "    Pseudo, "
                               "    Score "
                               "FROM Classement "
                               "WHERE Classement = ( "
                               "    SELECT Classement "
                               "    FROM Classement "
                               "    WHERE Pseudo = '%2' "
                               ") - 1;").arg(title).arg(user);
    QSqlQuery query(queryStr);

    if (!query.exec()) {
        qDebug() << query.lastError() << " Erreur lors de l'exécution de la requête getTopScoresInFrontUser ";

        return topScores;
    }

    if (query.next()) {
        ScoreInfoTop scoreInfo;
        scoreInfo.username = query.value(0).toString();
        scoreInfo.score = query.value(1).toLongLong();
        topScores.append(scoreInfo);
        qDebug() << "######################################## FIN + execution BDD getTopScoresInFrontUser ###################################################";
    } else {
        qDebug() << "Aucun Front score trouvé  : ";
        return topScores;
    }

    db.close();
    return topScores;
}
// Requête de pour la personne derrière l'utilisateur
QList<ScoreInfoTop> Database::getTopScoresBehindUser(const QString &title, const QString &user) {
    QList<ScoreInfoTop> topScores;

    qDebug() << title<<user;

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données getTopScoresInFronUse";
        return topScores;
    } else{
        qDebug() << "######################################## Ouverture BDD getTopScoresBehindUser ###################################################";
    }

    QString queryStr = QString("WITH Classement AS ( "
                               "    SELECT "
                               "        u.Pseudo, "
                               "        s.Score, "
                               "        j.Nom_jeu, "
                               "        ROW_NUMBER() OVER (PARTITION BY j.Nom_jeu ORDER BY s.Score DESC) AS Classement "
                               "    FROM scores s "
                               "    JOIN utilisateurs u ON s.ID_utilisateur = u.ID_utilisateur "
                               "    JOIN jeux j ON s.ID_jeu = j.ID_jeu "
                               "    WHERE j.Nom_jeu = '%1' "
                               ") "
                               "SELECT "
                               "    Pseudo, "
                               "    Score "
                               "FROM Classement "
                               "WHERE Classement = ( "
                               "    SELECT Classement "
                               "    FROM Classement "
                               "    WHERE Pseudo = '%2' "
                               ") + 1;").arg(title).arg(user);
    QSqlQuery query(queryStr);

    if (!query.exec()) {
        qDebug() << query.lastError() << " Erreur lors de l'exécution de la requête getTopScoresInFrontUser ";

        return topScores;
    }

    if (query.next()) {
        ScoreInfoTop scoreInfo;
        scoreInfo.username = query.value(0).toString();
        scoreInfo.score = query.value(1).toLongLong();
        topScores.append(scoreInfo);
        qDebug() << "######################################## FIN + execution BDD getTopScoresBehindUser ###################################################";
    } else {
        qDebug() << "Aucun Behind score trouvé  : ";
        return topScores;
    }

    db.close();
    return topScores;
}

Database::~Database(){
    closeDatabase();
}


