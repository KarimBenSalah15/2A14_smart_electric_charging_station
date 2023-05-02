#ifndef SERVICES_H
#define SERVICES_H
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QObject>
#include <QDate>
class Services
{
public:
    Services();
    Services(int,QString,int,int,QString,QDate);
    int getNum_Service();
    QString gettype();
    int getprix();
    int getduree();
    QDate getdate();
    QString getdisponibilite();
    void setNum_Service(int);
    void settype(QString);
    void setprix(int);
    void setdate(QDate);
    void setduree(int);
    void setdisponibilite(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * trier(QString);
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel *  afficher_calendar(QDate );
private:
    int Num_Service,prix,duree;
    QString type,disponibilite;
    QDate date_S;
};

#endif // SERVICES_H
