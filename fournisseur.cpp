#include "fournisseur.h"

Fournisseur::Fournisseur()
{
    id=0;
    type="";
    qer=0;
    cout=0;
}
Fournisseur::Fournisseur(int a, QString b, float c, float d)
{
    this->id=a;
    this->type=b;
    this->qer=c;
    this->cout=d;
}
int Fournisseur::getid()
{
    return id;
}
QString Fournisseur::gettype()
{
    return type;
}
float Fournisseur::getqer()
{
    return qer;
}
float Fournisseur::getcout()
{
    return cout;
}
void Fournisseur::setid(int nvid)
{
    this->id=nvid;
}

void Fournisseur::settype(QString nvtype)
{
    this->type=nvtype;
}
void Fournisseur::setqer(float nvqer)
{
    this->qer=nvqer;
}
void Fournisseur::setcout(float nvcout)
{
    this->cout=nvcout;
}
bool Fournisseur::ajouter()
{
    QSqlQuery query,query1;
    QString id_string= QString::number(id);
    QString cout_string= QString::number(cout);
    QString qer_string= QString::number(qer);
          query.prepare("INSERT INTO fournisseur (id_fournisseur, type, quantite_energie_recue, cout) "
                        "VALUES (:id, :type, :quantite_energie_recue, :cout)");
          query1.prepare("INSERT INTO historique (code_his, action, user_his) "
                        "VALUES (:code, 'ajouter', 'admin')");
          query.bindValue(":id", id_string);
          query.bindValue(":type", type);
          query.bindValue(":quantite_energie_recue", qer_string);
          query.bindValue(":cout", cout_string);

          query1.bindValue(":code", id_string);

          query.exec();
          return query1.exec();
}
QSqlQueryModel* Fournisseur::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM fournisseur");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité d'énergie reçue"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Coût"));
    return model;
}
bool Fournisseur::supprimer(int nvid)
{
    QSqlQuery query,query1;
    QString id_string= QString::number(id);
          query.prepare("Delete from fournisseur where id_fournisseur=:id");
          query1.prepare("INSERT INTO historique (code_his, action, user_his) ""select id_fournisseur, 'supprimer', 'admin' from fournisseur where id_fournisseur=:id");
          query.bindValue(":id", nvid);
          query1.bindValue(":id", nvid);
          query1.exec();
          return query.exec();
}
bool Fournisseur::modifier()

{
    QString id_string=QString::number(id);
    QString qer_string=QString::number(qer);
    QString cout_string=QString::number(cout);
    QSqlQuery query,query1;
          query.prepare("update "" fournisseur set  ID_fournisseur=:id, type=:type, QUANTITE_ENERGIE_RECUE=:qer, cout=:cout where id_fournisseur=:id " );
          query1.prepare("INSERT INTO historique (code_his, action, user_his) "
                        "VALUES (:code, 'modifier', 'admin')");
          query.bindValue(":id", id_string);
          query.bindValue(":type", type);
          query.bindValue(":qer", qer_string);
          query.bindValue(":cout", cout_string);
          query1.bindValue(":code", id_string);
          query1.exec();
          return query.exec();
}
QSqlQueryModel * Fournisseur::rechercher(QString chaine)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from fournisseur where ( ID_fournisseur LIKE'%"+chaine+"%' OR type LIKE'%"+chaine+"%' OR QUANTITE_ENERGIE_RECUE LIKE'%"+chaine+"%' OR cout LIKE'%"+chaine+"%') ");


    return model ;
}
QSqlQueryModel * Fournisseur::trier(QString test)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    if(test == "par défaut"){
        model->setQuery("SELECT * from fournisseur");
    }
    else if(test =="par type")
    {
        model->setQuery("SELECT * from fournisseur order by type asc ");
    }
    else if(test =="par cout")
    {
        model->setQuery("SELECT * from fournisseur order by cout asc ");
    }
    else if(test =="par id")
    {
        model->setQuery("SELECT * from fournisseur order by ID_fournisseur asc ");
    }
    else if(test =="par Quantite")
    {
        model->setQuery("SELECT * from fournisseur order by QUANTITE_ENERGIE_RECUE asc ");
    }

    return model;
}
QSqlQueryModel * Fournisseur::afficher_his()
{
  QSqlQueryModel * model=new QSqlQueryModel();

  model->setQuery("select * from historique ORDER BY DATE_HIS ");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("N°:"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("ACTION :"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("BY :"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE :"));

     return model;
}
