#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Réalisation d’un module IHM (Interface Homme-Machine) pour la commande d’un système de transmission vidéo embarqué d’un train");
    return a.exec();
}
