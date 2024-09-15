#include "mainwindow.h"
#include "inifilemanager.h"
#include "thread.h"

#include <QApplication>
#include <QScreen>
#include <QProcess>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Inifilemanager ini;

    QString model = ini.getModelFromFile();
    QString serial = ini.getSerialNumberFromFile();
    QString manufacturer = ini.getManufacturerFromFile();
    qDebug() << model << serial << manufacturer;


    QList<QScreen*> screens = QGuiApplication::screens();

// choix de l'ecran
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

    // Lancement du thread qui ferme l'application si PinuUpMenu est ferme
    QString processName = "PinUpMenu.exe";

    Thread thread(processName);

    thread.start();
    w.showFullScreen();
    return a.exec();
}
