#include <QPixmap>
#include<iostream>
#include"historique.h"
#include <QPainter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QSqlRecord>
#include <QTextDocument>
#include <QPdfWriter>
#include <QPieSeries>
#include <QChartView>
#include <QSqlRecord>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include"dialog_statist.h"
//#include<dialog_statistics.h>
#include <QPrinter>
#include <QPrintDialog>
#include"qrcode.hpp"
#include"exportexcel.h"
#include <QHeaderView>
#include<QDate>
#include <QPrinter>
#include <QPrintDialog>
#include <QPropertyAnimation>

#include <QtSerialPort/QSerialPort>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"voiture.h"
#include<QMessageBox>
#include<QDebug>
#include<QMainWindow>
#include<QIntValidator>
#include <QPieSeries>

#include <QtPrintSupport/QPrinter> // avant
#include <QPdfWriter>
#include<QPrinter>
#include <QTextDocument>
#include <QTextCursor>
#include<QSqlQueryModel>
#include<QtCharts>
#include<QPieSeries>
#include<QPieSlice>
#define SS_PIN 10
#define RST_PIN 9
#define LED_PIN 12
QT_CHARTS_USE_NAMESPACE
using namespace QtCharts;
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);


   int ret=A.connect_arduino(); // lancer la connexion à arduino
           switch(ret){
           case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
               break;
           case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
              break;
           case(-1):qDebug() << "arduino is not available";
           }
            QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_labelclient())); // permet de lancer
            //le slot update_label suite à la reception du signal readyRead (reception des données)



ui->lineEdit_Niveau_batterie->setValidator(new QIntValidator(0,100,this));
ui->tab_voiture->setModel(v.afficher());





}





MainWindow::~MainWindow()
{
   delete ui;
}
///////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_pushButton_clicked()
{

    QString MATRICULE=ui->lineEdit_Mat->text();
     QString TYPE_MOTEUR=ui->lineEdit_Type_moteur->text();
      QString TYPE_VOITURE=ui->lineEdit_Type_voiture->text();
       QString SANTE_BATTERIE=ui->lineEdit_Sante_batterie->text();
     int NIVEAU_BATTERIE=ui->lineEdit_Niveau_batterie->text().toInt();
     MATRICULE.remove(QRegExp("[^a-zA-Z0-9]"));
        TYPE_MOTEUR.remove(QRegExp("[^a-zA-Z0-9]"));
        TYPE_VOITURE.remove(QRegExp("[^a-zA-Z0-9]"));
        SANTE_BATTERIE.remove(QRegExp("[^a-zA-Z0-9]"));


     //ajout
     VOITURE V(MATRICULE,TYPE_VOITURE,TYPE_MOTEUR ,NIVEAU_BATTERIE,SANTE_BATTERIE);
     if(NIVEAU_BATTERIE<=0||TYPE_MOTEUR.isEmpty() || TYPE_VOITURE.isEmpty() || SANTE_BATTERIE.isEmpty() )
                          {
                              QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides Pour continuez."),QMessageBox::Cancel);
                          }
     bool test=V.ajouter();
     if (test){

             QMessageBox:: information(nullptr, QObject::tr("OK"),
                                                QObject::tr("Ajout Client effectué\n"
                                                            "click cancel to exit."),QMessageBox::Cancel);
             MATRICULE.clear();
             TYPE_MOTEUR.clear();
             TYPE_VOITURE.clear();
             SANTE_BATTERIE.clear();
}



}
/////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_pb_supprimer_clicked()
{
    VOITURE v1;
    v1.setMATRICULE(ui->lineEdit_Mat_supp->text());
    bool test=v1.supprimer(v1.getMATRICULE());
    if(test)
    {
        //TYPE_VOITUREresh
       ui->tab_voiture->setModel(v.afficher());

        QMessageBox::information( nullptr, QObject::tr("supprimé"),
                    QObject::tr("deleted successfully.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("pas supprimé"),
                    QObject::tr("Delete failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
/////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_pb_modifier_clicked()
{

        QString MATRICULE=ui->lineEdit_modif_mat->text();
        QString TYPE_VOITURE=ui->lineEdit_modif_type_voiture->text();
        QString TYPE_MOTEUR=ui->lineEdit_modif_type_moteur->text();
        int NIVEAU_BATTERIE=ui->lineEdit_modif_Niveau_batterie->text().toInt();
        QString SANTE_BATTERIE=ui->lineEdit_modif_Sante_batterie->text();
        VOITURE V(MATRICULE,TYPE_VOITURE,TYPE_MOTEUR,NIVEAU_BATTERIE,SANTE_BATTERIE);
        bool test=V.modifier(MATRICULE);
        if(test)
          { ui->tab_voiture->setModel(V.afficher());
       QMessageBox::information(nullptr, QObject::tr("modification avec succes"),
                   QObject::tr("Modification effectuée.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);}
        else
          QMessageBox::critical(nullptr, QObject::tr("erreur de modification"),
                      QObject::tr(" erreur.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

}
//////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_chercher_button_clicked()
{
    VOITURE v;
    QString MATRICULE=ui->matricule_a_chercher->text() ;
    ui->tab_voiture->setModel(v.rechercher(MATRICULE)) ;
    QMessageBox::information(nullptr, QObject::tr("succes"),
                QObject::tr(" affiche  dans le tableau !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::on_radioButton_croissant_clicked()
{
    ui->tab_voiture->setModel(v.tri());

}
////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_radioButton_dcroissant_clicked()
{
    ui->tab_voiture->setModel(v.trid());

}
/////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_export_pdf_clicked()
{
    QString strStream;
                             QTextStream out(&strStream);

                             const int rowCount = ui->tab_voiture->model()->rowCount();
                             const int columnCount = ui->tab_voiture->model()->columnCount();
                             QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                             out <<"<html>\n"
                                   "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                 << "<title>ERP - COMmANDE LIST<title>\n "
                                 << "</head>\n"
                                 "<body bgcolor=#ffffff link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\"><strong> ******LISTE DES  licence commerciale ******"+TT+" </strong></h1>"
                                 "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                   "</br> </br>";
                             // headers
                             out << "<thead><tr bgcolor=#d6e5ff>";
                             for (int column = 0; column < columnCount; column++)
                                 if (!ui->tab_voiture->isColumnHidden(column))
                                     out << QString("<th>%1</th>").arg(ui->tab_voiture->model()->headerData(column, Qt::Horizontal).toString());
                             out << "</tr></thead>\n";

                             // data table
                             for (int row = 0; row < rowCount; row++) {
                                 out << "<tr>";
                                 for (int column = 0; column < columnCount; column++) {
                                     if (!ui->tab_voiture->isColumnHidden(column)) {
                                         QString data =ui->tab_voiture->model()->data(ui->tab_voiture->model()->index(row, column)).toString().simplified();
                                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                     }
                                 }
                                 out << "</tr>\n";
                             }
                             out <<  "</table>\n"
                                 "</body>\n"
                                 "</html>\n";

                             QTextDocument *document = new QTextDocument();
                             document->setHtml(strStream);

                             QPrinter printer;

                             QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                             if (dialog->exec() == QDialog::Accepted) {
                                 document->print(&printer);
                             }

                             delete document;






}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_btn_export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        exportExcel obj(fileName, "mydata", ui->tab_voiture);

        //colums to export
        obj.addField(0, "MATRICULE", "char(20)");
        obj.addField(1, "TYPE_VOITURE", "char(20)");
        obj.addField(2, "TYPE_MOTEUR", "char(20)");
        obj.addField(3, "NIVEAU_BATTERIE", "int");
        obj.addField(4, "SANTE_BATTERIE", "char(20)");




        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButton_2_clicked()
{
    s = new Dialog_statist();
    s->setWindowTitle("Statistiques Par Etat");
    s->choix_pie();
    s->choix_bar();
    s->show();
}





void MainWindow::on_qrcodegen_2_clicked()
{

    int tab_emp=ui->tab_voiture->currentIndex().row(); // ligne
            QVariant idd=ui->tab_voiture->model()->data(ui->tab_voiture->model()->index(tab_emp,0));//selection de id et letre en variable idd
            QString MATRICULE= idd.toString();
            QSqlQuery qry;
            qry.prepare("SELECT * FROM VOITURE where MATRICULE=:MATRICULE");
            qry.bindValue(":MATRICULE",MATRICULE);
            qry.exec();
            QString TYPE_VOITURE,TYPE_MOTEUR,NIVEAU_BATTERIE,SANTE_BATTERIE,ids;

            while(qry.next()){
                TYPE_VOITURE=qry.value(1).toString();
                TYPE_MOTEUR=qry.value(2).toString();
                NIVEAU_BATTERIE=qry.value(3).toString();
                SANTE_BATTERIE=qry.value(4).toString();

            }
            ids=QString(MATRICULE);

            QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);//cripta chaine
            ids="MATRICULE: "+ids+" TYPE_VOITURE: "+TYPE_VOITURE+" TYPE_MOTEUR: "+TYPE_MOTEUR+" NIVEAU_BATTERIE: "+NIVEAU_BATTERIE+" SANTE_BATTERIE : "+SANTE_BATTERIE;

            // Read the black & white pixels
            QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
            for (int y = 0; y < qr.getSize(); y++) {
                for (int x = 0; x < qr.getSize(); x++) {
                    int color = qr.getModule(x, y);  // 0 for white, 1 for black

                    // You need to modify this part
                    if(color==0)
                        im.setPixel(x, y,qRgb(254, 254, 254));
                    else
                        im.setPixel(x, y,qRgb(0, 0, 0));
                }
            }
            im=im.scaled(200,200);
            ui->qrcodecommande_2->setPixmap(QPixmap::fromImage(im));

   }




void MainWindow::on_B_produit_Historique_2_clicked()
{
    QFile f("C:/Users/HP/Documents/myqtproject/historique.txt.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
        QString text = "  historique \r\n";
        QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
        outt << sDate;
        outt << text ;
        f.flush();
        f.close();
        if(!f.open(QFile::ReadOnly | QFile::Text))
        {
        QMessageBox::warning(this,"title","file not open");
        }
        QTextStream in(&f);
        QString textt = in.readAll();
        ui->plainTextEdit->setPlainText(textt);
        f.close();

}


void MainWindow::on_update_labelclient_clicked()
{
    data="";
    while ((A.getdata().size()<5)) {
    QString key;
    data=A.read_from_arduino();
    break;
    }
    if(data!=""){
        if(data.toInt()!=0)
         {
            int D=data.toInt();
            qDebug() << D;
            if(A.cherchercode(D)!=0)
            {A.write_to_arduino("1");

            }
            else{A.write_to_arduino("0");}
        }
    }
    data="";

}


