#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "Connexion.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("Connexion réussie.\n"
                                "Appuyez sur Cancel pour quitter."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("Echec de la connexion.\n"
                                "Appuyez sur Cancel pour quitter."), QMessageBox::Cancel);



    return a.exec();
}
