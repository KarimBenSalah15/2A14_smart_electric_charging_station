#ifndef empolyee_H
#define empolyee_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QVector>
#include <QDebug>
#include <QSqlQueryModel>
#include <QLineEdit>

using namespace std;

class empolyee
{
    public:
        empolyee();
        empolyee(int ID_EMPLOYE,QString NOM,QString PRENOM ,QString TYPE ,int NBR_HEURE,int SALAIRE) ;

            int getID_EMPLOYE();
            QString getNOM();
            QString getPRENOM();
            QString getTYPE();
            int getNBR_HEURE();
            int getSALAIRE();
            void setID_EMPLOYE(int);
            void setNOM(QString);
            void setPRENOM(int);
            void setEMAIL(QString);
            void setNBR_HEURE(int);
            void setSALAIRE(int);
            bool ajouter();
            QSqlQueryModel* afficher();
            bool supprimer(int);
            bool modifier(int);
             QSqlQueryModel * rechercher(QString );
            QSqlQueryModel * tri_asc();
                 QSqlQueryModel * tri_desc();

            int* nbRDV(int);

    private:
        int ID_EMPLOYE;
        QString NOM;
        QString PRENOM;
        QString TYPE;
        int NBR_HEURE;
        int SALAIRE;
};

#endif // empolyee_H
