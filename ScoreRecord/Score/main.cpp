#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QTimer>

#include "database.h"
#include "manager.h"
#include "inifilemanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Instanciation des Class
    Inifilemanager ini;
    Manager manager;
    QTimer timer;
    Database database;

    //Récuperation des données de HighscoreSystem dans le fichier Score/Score.ini (table joué, chemin du fichier de score, nom de l'utilisateur)
    QString title = ini.getTitleFromFile();
    QString path = ini.getPathFromFile();
    QString user = ini.getUsernameFromFile();


    //Remise a zéro du fichier Score/Score.ini pour éviter les triches
    manager.setByDefault();

    int intervalle = 1000; // Interval de 1 seconde (1000 ms)
    timer.setInterval(intervalle);

    qDebug()<<path<<user;
    qDebug()<<"Title is :"<<title;

    //Chemin du fichier a ouvrir pour récuperer le score
    QFile file(path);
    int tentatives = 5; // Nombre de tentatives
    int score = 0;


    int existing = 0;
    //vérification de l'éxistence du jeu
    existing = database.existGameDatabase(title);
    qDebug()<<existing;

    //Si le jeu n'existe pas dans nôtre BDD il stop le script
    if (existing < 1){
        database.closeDatabase();
        qDebug()<<"Fermeture app";
        return 1;
    }
    //Lecture + enregistrement des scores

    //Lancement du timer
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        qDebug() << "Le timer a déclenché !";

        //Récupération du meilleur score
        score = manager.recupererMeilleurScore(path);

        qDebug()<< title<<"TIIIIIIITTTRE";

        tentatives--;
        qDebug()<< tentatives;

        //Quand les tentatives de lecture sont finit
        if (tentatives < 0){

            //Enregistrement dans la BDD

            qDebug()<<"Enregistrement en cours "<<score;

            database.recordDatabase(title,user,score);
            timer.stop();
            database.closeDatabase();
            QCoreApplication::exit(0);
        }
    });


    timer.start();






    return a.exec();
}
