#ifndef VOITURE_H
#define VOITURE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QtCharts/QBarSet>
class VOITURE
{
public:
    VOITURE();
    VOITURE(QString,QString,QString,int ,QString );
    QString getMATRICULE();
    void setMATRICULE(QString MATRICULE);
    QString getTYPE_VOITURE();
    void setTYPE_VOITURE(QString TYPE_VOITURE);
    QString getTYPE_MOTEUR();
    void setTYPE_MOTEUR(QString TYPE_MOTEUR);
    QString getSANTE_BATTERIE();
   void setSANTE_BATTERIE(QString SANTE_BATTERIE);
    int  getNIVEAU_BATTERIE();
     void setNIVEAU_BATTERIE(int NIVEAU_BATTERIE);
    bool ajouter();
QSqlQueryModel *afficher();
bool supprimer(QString MATRICULE);
bool modifier(QString MATRICULE);
QSqlQueryModel *rechercher(QString);
QSqlQueryModel *tri();
 QSqlQueryModel * trid();
 static VOITURE Loginarduino(QString MATRICULE);

private:

    QString MATRICULE ;
    QString TYPE_VOITURE;
    QString TYPE_MOTEUR;
    int NIVEAU_BATTERIE;
     QString SANTE_BATTERIE;
};


#endif // VOITURE_H
