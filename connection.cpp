#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet2A");
db.setUserName("system");//insereAr nom de l'utilisateur
db.setPassword("12345");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
