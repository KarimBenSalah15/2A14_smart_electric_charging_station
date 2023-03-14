#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QObject>
class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(int,QString,float,float);
    int getid();
    QString gettype();
    float getqer();
    float getcout();
    void setid(int);
    void settype(QString);
    void setqer(float);
    void setcout(float);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
private:
    int id;
    QString type;
    float qer, cout;
};

#endif // FOURNISSEUR_H
