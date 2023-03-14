#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{
private:
    QSqlDatabase db;
public:
    Connection();
    bool createconnect();
    void closeconnect();
};
#endif // CONNEXION_H
