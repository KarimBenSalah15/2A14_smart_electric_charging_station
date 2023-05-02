#include "empolyee.h"
#include<QSqlQuery>
#include<QtDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QObject>
#include <QSqlQueryModel>


empolyee::empolyee()
{

ID_EMPLOYE=0;
NOM="";
PRENOM="";
TYPE="";
NBR_HEURE=0;
SALAIRE=0;
}


empolyee::empolyee (int ID_EMPLOYE, QString NOM, QString PRENOM , QString TYPE ,int NBR_HEURE,int SALAIRE)
{
    this->ID_EMPLOYE=ID_EMPLOYE;
    this->NOM=NOM ;
    this->PRENOM=PRENOM;
    this->TYPE =TYPE;
    this->NBR_HEURE=NBR_HEURE;
    this->SALAIRE=SALAIRE;


}
//getters
int empolyee::getID_EMPLOYE(){return  ID_EMPLOYE;}
QString empolyee::getNOM(){return NOM;}
QString empolyee::getPRENOM(){return PRENOM;}
QString empolyee ::getTYPE(){return TYPE;}
int empolyee ::getNBR_HEURE(){return NBR_HEURE;}
int empolyee ::getSALAIRE(){return SALAIRE;}
//setters
void empolyee::setID_EMPLOYE(int ID_EMPLOYE)
{this->ID_EMPLOYE=ID_EMPLOYE;}

void empolyee::setNOM(QString NOM)
{this->NOM=NOM;}

void empolyee::setPRENOM(int PRENOM)
{this->PRENOM=PRENOM;}

void empolyee::setEMAIL(QString TYPE)
{this->TYPE=TYPE;}

void empolyee::setNBR_HEURE(int NBR_HEURE)
{this->NBR_HEURE=NBR_HEURE;}

void empolyee::setSALAIRE(int SALAIRE)
{this->SALAIRE=SALAIRE;}

bool empolyee ::ajouter()
{
    QSqlQuery query;
    QString ID_string=QString::number(ID_EMPLOYE);
    QString NBR_HEURE_string=QString::number(NBR_HEURE);
       QString SALAIRE_string=QString::number(SALAIRE);
    query.prepare("INSERT INTO EMPLOYES VALUES (?,?,?,?,?,?)");
              query.addBindValue(ID_string);
              query.addBindValue(NOM);
              query.addBindValue(PRENOM);
              query.addBindValue(TYPE);
              query.addBindValue(NBR_HEURE_string);
              query.addBindValue(SALAIRE_string);

              return query.exec();
}

QSqlQueryModel* empolyee::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM EMPLOYES");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
         model->setHeaderData(3, Qt::Horizontal,QObject::tr("TYPE"));
         model->setHeaderData(4, Qt::Horizontal,QObject::tr("NBR_HEURE"));
         model->setHeaderData(5, Qt::Horizontal,QObject::tr("SALAIRE"));

    return  model ;
}

bool empolyee::supprimer(int ID_EMPLOYE)     //
{
   QSqlQuery query;
   QString ID_C=QString::number(ID_EMPLOYE);// conversion

  query.prepare("DELETE FROM EMPLOYES where ID_EMPLOYE = :ID ");
   query.bindValue(":ID",ID_C);
   return query.exec();
}
bool empolyee:: modifier(int ID_EMPLOYE)
{
    QSqlQuery query;
    QString ID_string = QString::number(ID_EMPLOYE);
   // QString PRENOM_string=QString::number(PRENOM);
    query.prepare("UPDATE EMPLOYES SET NOM=:NOM,PRENOM=:PRENOM,TYPE=:TYPE,SALAIRE=:SALAIRE,NBR_HEURE=:NBR_HEURE WHERE ID_EMPLOYE=:ID_EMPLOYE");
    query.bindValue(":ID_EMPLOYE",ID_string);
    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":TYPE",TYPE);
    query.bindValue(":NBR_HEURE",NBR_HEURE);
    query.bindValue(":SALAIRE",SALAIRE);
    return query.exec();
}
QSqlQueryModel*  empolyee::tri_asc()
{

    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM ID_EMPLOYE order by ID asc ");
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("NOM"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr(" PRENOM"));
          model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
          model->setHeaderData(3, Qt::Horizontal,QObject::tr("NBR_HEURE"));

    return model;
}
QSqlQueryModel*  empolyee::tri_desc()
{

    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM ID_EMPLOYE order by ID desc ");
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("NOM"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("PRENOM"));
          model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
          model->setHeaderData(3, Qt::Horizontal,QObject::tr("NBR_HEURE"));

    return model;
}
QSqlQueryModel* empolyee::rechercher(QString getNOM)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from ID_EMPLOYEE where ID LIKE '"+getNOM+"' ");
    return model;
}

