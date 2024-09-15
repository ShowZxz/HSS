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

    Inifilemanager ini;
    Manager manager;
    QTimer timer;
    Database database;

    //Récuperation des données de HighscoreSystem (table joué, chemin du fichier de score, nom de l'utilisateur)
    QString title = ini.getTitleFromFile();
    QString path = ini.getPathFromFile();
    QString user = ini.getUsernameFromFile();
    manager.setByDefault();

    int intervalle = 1000; // Interval de 1 seconde (1000 ms)
    timer.setInterval(intervalle);
    qDebug()<<path<<user;
    qDebug()<<"Title is :"<<title;

    QFile file(path);
    int tentatives = 5; // Nombre de tentatives
    int score = 0;


    int existing = 0;
    //vérification du jeu
    existing = database.existGameDatabase(title);
    qDebug()<<existing;


    if (existing < 1){
        database.closeDatabase();
        qDebug()<<"Fermeture app";
        return 1;
    }
    //Lecture + enregistrement des scores
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        qDebug() << "Le timer a déclenché !";
        score = manager.recupererMeilleurScore(path);
        QString title = manager.getTitleTable();
        qDebug()<< title<<"TIIIIIIITTTRE";
        database.recordDatabase(title,user,score);
        tentatives--;
        qDebug()<< tentatives;
        if (tentatives < 0){
            qDebug()<<"Enregistrement en cours"<<score;
            database.recordDatabase(title,user,score);
            timer.stop();
            database.closeDatabase();
            QCoreApplication::exit(0);
        }
    });


    timer.start();






    return a.exec();
}
