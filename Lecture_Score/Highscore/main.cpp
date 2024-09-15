
#include "database.h"

#include "inifilemanager.h"
#include "mainwindow.h"
#include "manager.h"
#include "thread.h"


#include "QLabel"


#include <windows.h>
#include <QProcess>
#include <QScreen>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;



    IniFileManager ini;
    Database database;
    Manager manager;

    QList<QScreen*> screens = QGuiApplication::screens();


    QString vpinball = "VPinballX.exe";


    QString worldUsername,topUsername,behindUsername,worldScore,topScore,behindScore,bestScore;


    worldScore = "None";
    topUsername = "None";
    behindScore = "None";
    worldScore = "None";
    topScore = "None";
    behindScore = "None";


    //Récupération des données du Setup.ini
    QString username = ini.getUsernameFromFile();
    QString password = ini.getPasswordFromFile();
    QString pathPinemhi = ini.getPinemhiPathFromFile();
    QString typeOfScreen = ini.getResolution();
    QString model = ini.getModelFromFile();
    QString serial = ini.getSerialNumberFromFile();
    QString manufacturer = ini.getManufacturerFromFile();
    qDebug() << model << serial << manufacturer;

    QList<LoginUser> resultLogin = database.getLoginUser(username, password);


    if (!username.isEmpty() || !password.isEmpty()) {


        if (resultLogin.isEmpty()) {
            QMessageBox::critical(nullptr, "Erreur Database", "L'utilisateur n'est pas inscrit ou erreur dans Setup.INI.");
            return 1;
        }

        //Verife useless
        if (resultLogin[0].pseudo != username || resultLogin[0].code != password) {
            QMessageBox::critical(nullptr, "Erreur", "Nom d'utilisateur ou mot de passe différent que celui de l'inscription.");
            return 1;
        }
    }
    //######################################################## LOGIQUE ARGV ###########################################################################


    if (argc < 2){
        QMessageBox::critical(nullptr, "Highscore System Error", "No argument, verify the pinup lauch script use [?ROM?] read the Read Me for more information");
        return 1;
    }


    //QString gameName = argv[1];
    QString rom = argv[1];
    //QString rom = "afm_113b";

    //QString gameName = "AC-DC";

    QString gameFullName=ini.getTitle(rom);

    qDebug()<<"@@@@@@@@@@@@@@@@@@@ gameFullName"+gameFullName;

    qDebug()<<"@@@@@@@@@@@@@@@@@@@"+rom;

    rom = rom+".txt";

    qDebug()<<"ROM = " <<rom;

    if (gameFullName.isEmpty()){
        rom ="";
    }

    qDebug()<<"ROM APRES TXT "+rom;

    QString processName = "Front.exe";
    //##################################################################################### PROCESS KILL ###################################################################################################

    //Fermeture de l'application Front
    QProcess *process = new QProcess();
    QStringList processList = process->systemEnvironment();
    processList << "tasklist";
    process->start("tasklist");
    process->waitForFinished(-1);

    QString tasklistOutput = process->readAllStandardOutput();

    if (tasklistOutput.contains(processName)) {

        QProcess::execute("taskkill",QStringList()<<"/F"<< "/IM" << processName);

    } else{

    }
    delete process;

    //######################################################## QUERY BDD ###########################################################################
    // User Highscore
    bestScore = database.getHighscoreFromDatabase(username,gameFullName);

    // Adversaire
    QList<ScoreInfoTop> result_WorldScore = database.getWorldHighscore(gameFullName);
    QList<ScoreInfoTop> result_Front = database.getTopScoresInFrontUser(gameFullName, username);
    QList<ScoreInfoTop> result_Behind = database.getTopScoresBehindUser(gameFullName, username);

    // Rank
    QString scoreInfo = database.getInfoRank(username,gameFullName);
    QString userRank = scoreInfo.right(1);


    QString strPosTop,strPosBottom;
    int rank = userRank.toInt();
    strPosTop = QString::number(rank - 1);
    strPosBottom = QString::number(rank + 1);




    foreach (const ScoreInfoTop& score, result_WorldScore) {

        //qDebug() <<"MAIN CPP WR : " + score.username << score.score;
        manager.setworldPosUser(score.username);
        manager.setworldPosScore(QString::number(score.score));
        //qDebug() <<"MAIN CPP WR MANAGER : " + manager.getworldPosScore();



    }
    foreach (const ScoreInfoTop& score, result_Front) {

        //qDebug() <<"MAIN CPP TOP INFO : " + score.username << score.score;
        manager.setfrontPosUser(score.username);
        manager.setfrontPosScore(QString::number(score.score));

    }

    foreach (const ScoreInfoTop& score, result_Behind) {

        //qDebug() <<"MAIN CPP BEHIND INFO : " + score.username << score.score;
        manager.setbehindPosUser(score.username);
        manager.setbehindPosScore(QString::number(score.score));

    }









    // affectation des valeur pour les noms et score
    worldUsername = manager.getworldPosUser();
    worldScore = manager.getworldPosScore();

    topUsername = manager.getfrontPosUser();
    topScore = manager.getfrontPosScore();

    behindUsername = manager.getbehindPosUser();
    behindScore = manager.getbehindPosScore();


    bestScore=manager.formatStringWithSpaces(bestScore);
    topScore=manager.formatStringWithSpaces(topScore);
    behindScore=manager.formatStringWithSpaces(behindScore);
    worldScore=manager.formatStringWithSpaces(worldScore);

    strPosTop = manager.setZeroToOne(strPosTop);

    qDebug() << "MAIN CPP GLOBAL INFO : "<< " Le meilleur score de : "+ username +" = "+ bestScore +"Rank : #"+ userRank <<
        "LE MEILLEUR sur la table :" +gameFullName+" NAME : Rank #1 " + worldUsername + " " +worldScore
             << "FRONT USER = : Rank #" +strPosTop+" "+ topUsername + " " +topScore<<
        "BEHIND USER = :Rank #" + strPosBottom +" " + behindUsername + " " +behindScore;


    //########################################################################## Config screen ##########################################################################








    QString styleSheetNumber;
    QString styleSheetName;
    QString styleSheetRank;

    QLabel *myBestScoreLabel,*worldRecordLabel,*topScoreLabel,*midScoreLabel,*botScoreLabel,*midRankLabel,*botRankLabel,*topRankLabel,*myRankLabel,*worldRankLabel,*myName,
        *worldName,*topName,*botName,*midName;








    // Trouver l'écran correspondant
    QScreen* targetScreen = nullptr;
    for (QScreen* screen : screens) {
        if (screen->manufacturer() == manufacturer && screen->model() == model && screen->serialNumber() == serial) {
            targetScreen = screen;
            break;
        }
    }

    // Déplacer la fenêtre vers l'écran trouvé
    if (targetScreen) {
        QRect geometry = targetScreen->geometry();
        w.move(geometry.x(), geometry.y());
        qDebug() << "Application déplacé";
    } else {
        qDebug() << "Aucun écran correspondant trouvé.";
    }


/*
    if (screens.size() > displayScreen) {
        QScreen* scr = screens.at(displayScreen);



        w.move(scr->geometry().x(), scr->geometry().y());

    }*/

    // Si la table n'est pas supporté
    if (rom.isEmpty()){
        /*
        QMessageBox msgBox(QMessageBox::Warning, "Avertissement", "<font color='red'> Empty Nvram , The GAMEFULLNAME doesnt match with the Nvram verify rom.ini or this table is not SUPPORTED by HIGHSCORESYTEM !</font>", QMessageBox::Ok, &w);
        msgBox.setWindowTitle("HIGHSCORE SYSTEM : Error ");
        msgBox.exec();
        */

        bestScore="NOT SUPPORTED";
        qDebug()<<"VIDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDE";
        worldScore="NOT SUPPORTED";
        //myBestScoreLabel->setText("NOT SUPPORTED");
        //worldRecordLabel->setText("NOT SUPPORTED");

    }

//#############################################################################SETUP SCREEN##############################################################################################
//mise en place des label suivant les deux resolution disponible
    if ( !typeOfScreen.isEmpty()){
        if (typeOfScreen == "1280 x 720") {
            styleSheetNumber = "font-size: 30px; color: red; font-weight: bold; background: transparent; border: none;";
            styleSheetName = "font-size: 15px; color: red; font-weight: bold; background: transparent; border: none;";
            styleSheetRank = "font-size: 20px; color: red; font-weight: bold; background: transparent; border: none;";

            myBestScoreLabel = new QLabel("100000000000", &w);
            myBestScoreLabel->setGeometry(220, 235, 400, 110);
            myBestScoreLabel->setAlignment(Qt::AlignCenter);
            myBestScoreLabel->setStyleSheet(styleSheetNumber);

            worldRecordLabel = new QLabel("100000000000", &w);
            worldRecordLabel->setGeometry(220, 405, 400, 110);
            worldRecordLabel->setAlignment(Qt::AlignCenter);

            topScoreLabel = new QLabel("100000000000", &w);
            topScoreLabel->setGeometry(700, 245, 400, 110);
            topScoreLabel->setAlignment(Qt::AlignCenter);

            midScoreLabel = new QLabel("100000000000", &w);
            midScoreLabel->setGeometry(700, 330, 400, 110);
            midScoreLabel->setAlignment(Qt::AlignCenter);

            botScoreLabel = new QLabel("100000000000", &w);
            botScoreLabel->setGeometry(700, 415, 400, 110);
            botScoreLabel->setAlignment(Qt::AlignCenter);

            botRankLabel = new QLabel("100", &w);
            botRankLabel->setGeometry(1040, 400, 50, 110);
            botRankLabel->setAlignment(Qt::AlignCenter);

            midRankLabel = new QLabel("100", &w);
            midRankLabel->setGeometry(1040, 320, 50, 110);
            midRankLabel->setAlignment(Qt::AlignCenter);

            topRankLabel = new QLabel("100", &w);
            topRankLabel->setGeometry(1040, 235, 50, 110);
            topRankLabel->setAlignment(Qt::AlignCenter);

            myRankLabel = new QLabel("1000", &w);
            myRankLabel->setGeometry(565, 235, 50, 110);
            myRankLabel->setAlignment(Qt::AlignCenter);

            worldRankLabel = new QLabel("1", &w);
            worldRankLabel->setGeometry(565, 400, 50, 110);
            worldRankLabel->setAlignment(Qt::AlignCenter);

            myName = new QLabel("COUCOU C MOI", &w);
            myName->setGeometry(150, 210, 400, 110);
            myName->setAlignment(Qt::AlignCenter);

            worldName = new QLabel("LE MEILLEUR", &w);
            worldName->setGeometry(150, 380, 400, 110);
            worldName->setAlignment(Qt::AlignCenter);

            topName = new QLabel("C++ QTCREATOR", &w);
            topName->setGeometry(590, 220, 400, 110);
            topName->setAlignment(Qt::AlignCenter);

            midName = new QLabel("YOU", &w);
            midName->setGeometry(570, 310, 400, 110);
            midName->setAlignment(Qt::AlignCenter);

            botName = new QLabel("THE MONSTER", &w);
            botName->setGeometry(590, 390, 400, 110);
            botName->setAlignment(Qt::AlignCenter);

            myBestScoreLabel->setStyleSheet(styleSheetNumber);
            worldRecordLabel->setStyleSheet(styleSheetNumber);
            topScoreLabel->setStyleSheet(styleSheetNumber);
            midScoreLabel->setStyleSheet(styleSheetNumber);
            botScoreLabel->setStyleSheet(styleSheetNumber);

            myRankLabel->setStyleSheet(styleSheetRank);
            botRankLabel->setStyleSheet(styleSheetRank);
            midRankLabel->setStyleSheet(styleSheetRank);
            topRankLabel->setStyleSheet(styleSheetRank);
            worldRankLabel->setStyleSheet(styleSheetRank);

            myName->setStyleSheet(styleSheetName);
            worldName->setStyleSheet(styleSheetName);
            botName->setStyleSheet(styleSheetName);
            midName->setStyleSheet(styleSheetName);
            topName->setStyleSheet(styleSheetName);

        }
        if(typeOfScreen == "1920 x 1080"){
            styleSheetNumber = "font-size: 30px; color: red; font-weight: bold; background: transparent; border: none;";
            styleSheetName = "font-size: 20px; color: red; font-weight: bold; background: transparent; border: none;";
            styleSheetRank = "font-size: 20px; color: red; font-weight: bold; background: transparent; border: none;";

            myBestScoreLabel = new QLabel("100000000000", &w);
            myBestScoreLabel->setGeometry(430, 390, 400, 110);
            myBestScoreLabel->setAlignment(Qt::AlignCenter);
            myBestScoreLabel->setStyleSheet(styleSheetNumber);

            worldRecordLabel = new QLabel("100000000000", &w);
            worldRecordLabel->setGeometry(430, 640, 400, 110);
            worldRecordLabel->setAlignment(Qt::AlignCenter);

            topScoreLabel = new QLabel("100000000000", &w);
            topScoreLabel->setGeometry(1150, 400, 400, 110);
            topScoreLabel->setAlignment(Qt::AlignCenter);

            midScoreLabel = new QLabel("100000000000", &w);
            midScoreLabel->setGeometry(1150, 520, 400, 110);
            midScoreLabel->setAlignment(Qt::AlignCenter);

            botScoreLabel = new QLabel("100000000000", &w);
            botScoreLabel->setGeometry(1150, 650, 400, 110);
            botScoreLabel->setAlignment(Qt::AlignCenter);

            botRankLabel = new QLabel("100", &w);
            botRankLabel->setGeometry(1575, 640, 50, 110);
            botRankLabel->setAlignment(Qt::AlignCenter);

            midRankLabel = new QLabel("100", &w);
            midRankLabel->setGeometry(1575, 515, 50, 110);
            midRankLabel->setAlignment(Qt::AlignCenter);

            topRankLabel = new QLabel("100", &w);
            topRankLabel->setGeometry(1575, 390, 50, 110);
            topRankLabel->setAlignment(Qt::AlignCenter);

            myRankLabel = new QLabel("100", &w);
            myRankLabel->setGeometry(860, 380, 50, 110);
            myRankLabel->setAlignment(Qt::AlignCenter);

            worldRankLabel = new QLabel("1", &w);
            worldRankLabel->setGeometry(860, 630, 50, 110);
            worldRankLabel->setAlignment(Qt::AlignCenter);

            myName = new QLabel("COUCOU C MOI", &w);
            myName->setGeometry(380, 350, 400, 110);
            myName->setAlignment(Qt::AlignCenter);

            worldName = new QLabel("LE MEILLEUR", &w);
            worldName->setGeometry(380, 600, 400, 110);
            worldName->setAlignment(Qt::AlignCenter);

            topName = new QLabel("C++ QTCREATOR", &w);
            topName->setGeometry(1020, 360, 400, 110);
            topName->setAlignment(Qt::AlignCenter);

            midName = new QLabel( &w);
            midName->setGeometry(1020, 490, 400, 110);
            midName->setAlignment(Qt::AlignCenter);

            botName = new QLabel("THE MONSTER", &w);
            botName->setGeometry(1020, 610, 400, 110);
            botName->setAlignment(Qt::AlignCenter);

            myBestScoreLabel->setStyleSheet(styleSheetNumber);
            worldRecordLabel->setStyleSheet(styleSheetNumber);
            topScoreLabel->setStyleSheet(styleSheetNumber);
            midScoreLabel->setStyleSheet(styleSheetNumber);
            botScoreLabel->setStyleSheet(styleSheetNumber);

            myRankLabel->setStyleSheet(styleSheetRank);
            botRankLabel->setStyleSheet(styleSheetRank);
            midRankLabel->setStyleSheet(styleSheetRank);
            topRankLabel->setStyleSheet(styleSheetRank);
            worldRankLabel->setStyleSheet(styleSheetRank);

            myName->setStyleSheet(styleSheetName);
            worldName->setStyleSheet(styleSheetName);
            botName->setStyleSheet(styleSheetName);
            midName->setStyleSheet(styleSheetName);
            topName->setStyleSheet(styleSheetName);

        }

    } else{
        QMessageBox msgBox(QMessageBox::Critical, "Avertissement", "<font color='red'> NO SCREEN IN SETUP.INI !</font>", QMessageBox::Ok, &w);
        msgBox.setWindowTitle("HIGHSCORE SYSTEM : Error ");
        msgBox.exec();
        return 1;
        //NO SCREEN IN SETUP.INI
    }


    //setup of label
    myBestScoreLabel->setText(bestScore); worldRecordLabel->setText(worldScore); topScoreLabel->setText(topScore); botScoreLabel->setText(behindScore); midScoreLabel->setText(bestScore);
    worldName->setText(worldUsername); myName->setText(username); topName->setText(topUsername); midName->setText(username); botName->setText(behindUsername);
    botRankLabel->setText(strPosBottom); midRankLabel->setText(userRank); topRankLabel->setText(strPosTop); myRankLabel->setText(userRank); worldRankLabel->setText("1");

    //########################################################################THREAD#############################################################################################################



    //#####################################################################################PROCESS################################################################################################
    //thread si visualpinball est fermé ou pas
    Thread thread(vpinball,username,gameFullName,pathPinemhi,rom);
    thread.start();

    w.showFullScreen();





    return a.exec();
}
