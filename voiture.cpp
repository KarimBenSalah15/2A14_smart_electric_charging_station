#include "voiture.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
VOITURE::VOITURE()
{



MATRICULE="";
TYPE_VOITURE="";
TYPE_MOTEUR="";
NIVEAU_BATTERIE=0;
SANTE_BATTERIE="";

}
VOITURE::VOITURE(QString MATRICULE,QString TYPE_VOITURE,QString TYPE_MOTEUR,int NIVEAU_BATTERIE,QString SANTE_BATTERIE)
{
   this->MATRICULE=MATRICULE;
   this->TYPE_VOITURE=TYPE_VOITURE;
   this->TYPE_MOTEUR=TYPE_MOTEUR;
   this->NIVEAU_BATTERIE=NIVEAU_BATTERIE;
   this->SANTE_BATTERIE=SANTE_BATTERIE;
}
QString VOITURE::getMATRICULE()
{
   return MATRICULE;
}
void VOITURE::setMATRICULE(QString MATRICULE)
{
   this->MATRICULE=MATRICULE;

}
QString VOITURE::getTYPE_VOITURE()
{
   return TYPE_VOITURE;
}
void VOITURE::setTYPE_VOITURE(QString TYPE_VOITURE)
{
   this->TYPE_VOITURE=TYPE_VOITURE;

}
QString VOITURE::getTYPE_MOTEUR()
{
   return TYPE_MOTEUR;
}
void VOITURE::setTYPE_MOTEUR(QString TYPE_MOTEUR)
{
   this->TYPE_MOTEUR=TYPE_MOTEUR;
}
QString VOITURE::getSANTE_BATTERIE()
{
   return SANTE_BATTERIE;
}
void VOITURE::setSANTE_BATTERIE(QString SANTE_BATTERIE)
{
   this->SANTE_BATTERIE=SANTE_BATTERIE;



}
int  VOITURE::getNIVEAU_BATTERIE()
{
   return  NIVEAU_BATTERIE;
}
void VOITURE::setNIVEAU_BATTERIE(int NIVEAU_BATTERIE)
{
    this->NIVEAU_BATTERIE=NIVEAU_BATTERIE;
}

bool VOITURE::ajouter(){

    QSqlQuery query;
    QString NIVEAU_BATTERIE_string = QString::number(NIVEAU_BATTERIE);
         query.prepare("INSERT INTO VOITURE (MATRICULE,TYPE_VOITURE,TYPE_MOTEUR,NIVEAU_BATTERIE,SANTE_BATTERIE) "
                       "VALUES (:MATRICULE, :TYPE_VOITURE, :TYPE_MOTEUR, :NIVEAU_BATTERIE, :SANTE_BATTERIE)");
         query.bindValue(":MATRICULE", MATRICULE);
         query.bindValue(":TYPE_VOITURE", TYPE_VOITURE);
         query.bindValue(":TYPE_MOTEUR", TYPE_MOTEUR);
         query.bindValue(":NIVEAU_BATTERIE", NIVEAU_BATTERIE);
         query.bindValue(":SANTE_BATTERIE", SANTE_BATTERIE);
         query.exec();


         return query.exec();
}
QSqlQueryModel * VOITURE::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from VOITURE");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("MATRICULE"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_VOITURE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE_MOTEUR"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("NIVEAU_BATTERIE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("SANTE_BATTERIE"));
return model;
}
bool VOITURE::supprimer(QString MATRICULE){
    QSqlQuery query;
         query.prepare(" DELETE FROM VOITURE WHERE MATRICULE=:MATRICULE");
         query.bindValue(":MATRICULE", MATRICULE);
         query.exec();
         return query.exec();

}
bool VOITURE:: modifier(QString MATRICULE)
{
    QSqlQuery query;
    QString NIVEAU_BATTERIE_string = QString::number(NIVEAU_BATTERIE);
    query.prepare("Update VOITURE SET MATRICULE=:MATRICULE,TYPE_VOITURE=:TYPE_VOITURE,TYPE_MOTEUR=:TYPE_MOTEUR,NIVEAU_BATTERIE=:NIVEAU_BATTERIE,SANTE_BATTERIE=:SANTE_BATTERIE WHERE MATRICULE=:MATRICULE");
    query.bindValue(":MATRICULE", MATRICULE);
    query.bindValue(":TYPE_VOITURE", TYPE_VOITURE);
    query.bindValue(":TYPE_MOTEUR", TYPE_MOTEUR);
    query.bindValue(":NIVEAU_BATTERIE",NIVEAU_BATTERIE_string);
    query.bindValue(":SANTE_BATTERIE", SANTE_BATTERIE);
    return query.exec();
}
QSqlQueryModel * VOITURE::rechercher(QString MATRICULE)
{
QSqlQueryModel * model= new QSqlQueryModel();
QSqlQuery query;
query.prepare("SELECT * from VOITURE where MATRICULE= :MATRICULE");
query.bindValue(":MATRICULE",MATRICULE);

    query.exec();
model->setQuery(query);
model->setHeaderData(0, Qt::Horizontal,QObject::tr("MATRICULE"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("TYPE_VOITURE"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE_MOTEUR"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("NIVEAU_BATTERIE"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("SANTE_BATTERIE"));


return model ;
}
QSqlQueryModel *VOITURE::tri(){

       QSqlQuery *q = new QSqlQuery();
       QSqlQueryModel *model = new QSqlQueryModel();
       q->prepare("SELECT * FROM VOITURE ORDER BY MATRICULE ");
       q->exec();
       model->setQuery(*q);

       return model;
    }

    QSqlQueryModel *VOITURE::trid(){

       QSqlQuery *q = new QSqlQuery();
       QSqlQueryModel *model = new QSqlQueryModel();
       q->prepare("SELECT * FROM VOITURE ORDER BY MATRICULE DESC");
       q->exec();
       model->setQuery(*q);

       return model;
    }
    VOITURE VOITURE::Loginarduino(QString MATRICULE) {
        VOITURE v;
        qDebug() << "matricule rech " << MATRICULE ;
        v.setMATRICULE("");
        QSqlQuery query;
        query.prepare("SELECT * from VOITURE WHERE MATRICULE=:E3 97 54 A7 ");
        query.prepare("INSERT INTO VOITURE (MATRICULE,TYPE_VOITURE,TYPE_MOTEUR,NIVEAU_BATTERIE,SANTE_BATTERIE) "
                      "VALUES (:MATRICULE, :TYPE_VOITURE, :TYPE_MOTEUR, :NIVEAU_BATTERIE, :SANTE_BATTERIE)");
        query.bindValue(":MATRICULE", MATRICULE);

        query.exec();

        query.bindValue(":MATRICULE", MATRICULE);

        if (query.exec() && query.first()) {
            qDebug() << "value 0 " << query.value(0).toString() ;
            v.setMATRICULE(query.value(0).toString());
            v.setTYPE_VOITURE(query.value(1).toString());
            v.setTYPE_MOTEUR(query.value(2).toString());
            v.setNIVEAU_BATTERIE(query.value(3).toInt());
            v.setSANTE_BATTERIE(query.value(4).toString());
        } else {
            qDebug() << "error" << v.getMATRICULE() ;
        }
        return v;
    }
