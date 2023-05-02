#include "services.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Services::Services()
{
Num_Service=0;
type="";
prix=0;
duree=0;
disponibilite="";
}
Services::Services(int Num_Service,QString type,int prix,int duree,QString disponibilite,QDate date)
{
    this->Num_Service=Num_Service;
    this->type=type;
    this->prix=prix;
    this->duree=duree;
    this->disponibilite=disponibilite;
    this->date_S=date;
}
int Services::getNum_Service(){return Num_Service;}
QString Services::gettype(){return type;}
QDate Services::getdate(){return date_S;}
int Services::getprix(){return prix;}
int Services::getduree(){return duree;}
QString Services::getdisponibilite(){return disponibilite;}
void Services::setNum_Service(int Num_Service){this->Num_Service=Num_Service;}
void Services::settype(QString type){this->type=type;}
void Services::setprix(int prix){this->prix=prix;}
void Services::setdate(QDate date){this->date_S=date;}
void Services::setduree(int duree){this->duree=duree;}
void Services::setdisponibilite(QString disponibilite){this->disponibilite=disponibilite;}
bool Services::ajouter()

{
    QString Num_Service_string=QString::number(Num_Service);
        QString prix_string=QString::number(prix);
        QString duree_string=QString::number(duree);
        QSqlQuery query;
              query.prepare("INSERT INTO SERVICE (num_service, type, prix, duree, disponibilite,date_S) "
                            "VALUES (:num_service, :type, :prix, :duree, :disponibilite, :date)");
              query.bindValue(":num_service", Num_Service_string);
              query.bindValue(":type", type);
              query.bindValue(":date", date_S);
              query.bindValue(":prix", prix_string);
              query.bindValue(":duree", duree_string);
              query.bindValue(":disponibilite", disponibilite);
              return query.exec();


    }
bool Services::supprimer(int Num_Service)
{
    QSqlQuery query;
          query.prepare(" Delete from service where num_service=:num_service");
          query.bindValue(0, Num_Service);

          return query.exec();



}
QSqlQueryModel* Services::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT* FROM service");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero du service"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Disponibilite"));




    return model;
}
bool Services::modifier(int Num_Service)

{
    QSqlQuery query;

               QString res=QString::number(Num_Service);

        QString res1;
        res1.setNum(prix);

                 query.prepare("UPDATE service SET Num_Service=:Num_Service, TYPE=:type, duree=:duree , date_S=:date, prix=:prix,  disponibilite =:disponibilite where Num_Service='"+res+"' ");

                       query.bindValue(":Num_Service", res);
                       query.bindValue(":type", type);
                       query.bindValue(":duree",duree);
                       query.bindValue(":prix", res1);


                       query.bindValue(":date", date_S);
                       query.bindValue(":disponibilite", disponibilite);







        return query.exec();


}
QSqlQueryModel * Services::rechercher(QString chaine)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from service where ( Num_Service LIKE'%"+chaine+"%' OR type LIKE'%"+chaine+"%' OR prix LIKE'%"+chaine+"%' OR duree LIKE'%"+chaine+"%' OR DISPONIBILITE LIKE'%"+chaine+"%') ");


    return model ;
}
QSqlQueryModel * Services::trier(QString test)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    if(test == "par défaut"){
        model->setQuery("SELECT * from service");
    }
    else if(test =="par type")
    {
        model->setQuery("SELECT * from service order by TYPE asc ");
    }
    else if(test =="par prix")
    {
        model->setQuery("SELECT * from service order by PRIX asc ");
    }
    else if(test =="par Num_Service")
    {
        model->setQuery("SELECT * from service order by NUM_SERVICE asc ");
    }
    else if(test =="par duree")
    {
        model->setQuery("SELECT * from service order by DUREE asc ");
    }
    else if(test =="par disponibilite")
    {
        model->setQuery("SELECT * from service order by DISPONIBILITE asc ");
    }
    return model;
}
QSqlQueryModel * Services:: afficher_calendar(QDate x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
QString x1=QString::number(x.month()),x2=QString::number(x.day()),x3=QString::number(x.year());
model->setQuery("select * from service where(extract(day  from date_S)='"+x2+"' and extract(month  from date_S)='"+x1+"' and extract(year  from date_S)='"+x3+"')");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num_Service"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("disponibilite"));

    return model;
}
