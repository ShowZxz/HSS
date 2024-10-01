#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Fonction pour debug l'écran sélectionné dans le comboBox
void MainWindow::on_comboBox_ScreeNumber_currentIndexChanged(int index)
{
    int selectedValue = index + 1 ;
    qDebug() << "Écran sélectionné :"<< selectedValue;

}

// Fonction du bouton de vérification (Test)
void MainWindow::on_pushButton_testScreen_clicked()
{
    // Fabricant et le numéro de serie de l'écran
    QString manu,serial,model;
    // Récupération de l'index du comboBox
    int selectedScreenIndex = ui->comboBox_ScreeNumber->currentIndex();

    qDebug() << "SELECT SCREEN"<<selectedScreenIndex;

    // Récupérer la liste des écrans détectés par Qt

    QList<QScreen*> screens = QGuiApplication::screens();

    // Vérifier si l'index sélectionné est valide parmis les écrans branché
    if (selectedScreenIndex >= 0 && selectedScreenIndex < screens.size()) {
        // Récupérer l'écran correspondant à l'index sélectionné
        QScreen *selectedScreen = screens.at(selectedScreenIndex);

        // Afficher des informations sur l'écran sélectionné en debug
        qDebug() << "Écran sélectionné :" << selectedScreen->name();
        qDebug() << "Serial Number:" << selectedScreen->serialNumber();
        qDebug() << "Model:" << selectedScreen->model();
        qDebug() << "Manufacturer:" << selectedScreen->manufacturer();
        qDebug() << "Résolution :" << selectedScreen->geometry().width() << "x" << selectedScreen->geometry().height();
        qDebug() << "Position :" << selectedScreen->geometry().x() << "," << selectedScreen->geometry().y();

        //Affectation des valeurs au variable
        manu = selectedScreen->manufacturer();
        model = selectedScreen->model();
        serial = selectedScreen->serialNumber();
        // Stockage des variable dans la class Manager
        man.setSerial(serial);
        man.setManufacturer(manu);
        man.setModel(model);

        // Affichage de l'information a l'utilisateur avec la création d'une tram
        QString scr = "Écran sélectionné : " + selectedScreen->name();
        int t = selectedScreen->geometry().width();
        int z = selectedScreen->geometry().height();
        QString i = QString::number(t);
        QString j = QString::number(z);
           // QString res = "Résolution :" + QString::number(selected) + "x" << selectedScreen->geometry().height();
        //La trame a afficher a l'utilisateur
        QString tram = scr + " Résolution : " + i + " x "+j;
        //Affichage avec un QMessageBox
        QMessageBox::information(this, "SCREEN TEST", tram);
    } else {

        qDebug() << "L'index sélectionné n'est pas valide.";
    }
}

// Fonction pour debug l'écran sélectionné dans le comboBox pour la résolution d'écran
void MainWindow::on_comboBox_Resolution_currentTextChanged(const QString &arg1)
{
    QString selectedString = arg1;
    qDebug() << "Selected String: " << selectedString;
}

// Enregistrement des informations inscrit par l'utilisateur
void MainWindow::on_pushButton_Save_clicked()
{
    QString manu,serial,model;
    //Récuperation des valeur stocké dans la Class Manager
    manu = man.getManufacturer();
    model = man.getModel();
    serial = man.getSerial();
    qDebug() << manu << serial << model;
    //Récupération des valeurs dans l'ui
    QString display = ui->comboBox_ScreeNumber->currentText();
    QString screenRes = ui->comboBox_Resolution->currentText();

    QString username = ui->lineEdit_username->text();
    QString code = ui->lineEdit_code->text();

    qDebug()<<display<<screenRes<<username<<code;

    //Vérification que tout les chanmps soit remplis
    if (!display.isEmpty() && !screenRes.isEmpty() && !username.isEmpty() && !code.isEmpty()){



        QSettings settings("Config/Setup.ini", QSettings::IniFormat);
        QString path_leaderboard = "PINemHi/PINemHi LeaderBoard/TOP10_Personal/";

        //Liste des info a rentrer dans le fichier Setup.ini
        settings.beginGroup("SCREEN");
        settings.setValue("Display", display);
        settings.setValue("SerialNumber",serial);
        settings.setValue("Manufacturer",manu);
        settings.setValue("Model",model);
        settings.endGroup();

        settings.beginGroup("USER");
        settings.setValue("Username", username);
        settings.setValue("Password", code);
        settings.endGroup();

        settings.beginGroup("PATH");
        settings.setValue("Leaderboard", path_leaderboard);
        settings.endGroup();

        settings.beginGroup("SCALE");
        settings.setValue("Size_screen", screenRes);
        settings.endGroup();


        QMessageBox::information(this, "Sucess", "Values ​​have been changed in ini. File");
    } else {

        QMessageBox::critical(nullptr, "Erreur", "All slots are not fully complete");
    }
}

// Link redirect pour l'inscription et recevoir le code a ajouter
void MainWindow::on_pushButton_Inscription_clicked()
{
    QUrl url("https://highscoresystem.com");


    QDesktopServices::openUrl(url);
}

