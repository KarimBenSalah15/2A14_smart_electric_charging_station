#include "historique.h"


historique::historique()
{

}
void historique::save(QString id,QString quantite)
{    QFile file ("C:/hamzaaa/histo.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << id+"\n"+quantite << "\n";


}
QString historique::load()
{   tmp="";
    QFile file("C:/hamzaaa/histo.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
