#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include "QPainter"
#include "QPrinter"
#include "QPainter"
#include "QtPrintSupport/QPrinter"
#include "QPdfWriter"
#include "QDesktopServices"
#include "QUrl"
#include "QTimer"
#include "QDate"
#include <QtCharts>
#include <QPieSeries>
#include "QPrintDialog"
#include "smtp.h"
#include "Arduino.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(100, 9999999, this));
 ui->tableView->setModel(F.afficher());
    //ui->tab_fournisseur->setModel(F.afficher());
 ui->comboBox_tri->addItem("par défaut");
 ui->comboBox_tri->addItem("par id");
     ui->comboBox_tri->addItem("par type");
     ui->comboBox_tri->addItem("par Quantite");
     ui->comboBox_tri->addItem("par cout");
     ui->le_id->setValidator(new QIntValidator(0,9999999, this));
         ui->le_id_2->setValidator(new QIntValidator(0,9999999, this));


         ui->le_type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
         ui->le_type_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));

         QDoubleValidator *validator = new QDoubleValidator(0.0, 100.0, 2, ui->le_qer);
         validator->setNotation(QDoubleValidator::StandardNotation);
         ui->le_qer->setValidator(validator);

         QDoubleValidator *validator1 = new QDoubleValidator(0.0, 100.0, 2, ui->le_qer_2);
         validator1->setNotation(QDoubleValidator::StandardNotation);
         ui->le_qer_2->setValidator(validator1);
         QDoubleValidator *validator2 = new QDoubleValidator(0.0, 100.0, 2, ui->le_cout);
         validator2->setNotation(QDoubleValidator::StandardNotation);
         ui->le_cout->setValidator(validator2);
         QDoubleValidator *validator3 = new QDoubleValidator(0.0, 100.0, 2, ui->le_cout_2);
         validator3->setNotation(QDoubleValidator::StandardNotation);
         ui->le_cout_2->setValidator(validator3);
         connect(ui->sendBtn_2, SIGNAL(clicked()),this, SLOT(sendMail()));
                       connect(ui->browseBtn_2, SIGNAL(clicked()), this, SLOT(browse()));
                       int ret=A.connect_arduino(); // lancer la connexion à arduino
                           switch(ret){
                           case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                               break;
                           case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                              break;
                           case(-1):qDebug() << "arduino is not available";
                           }
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    QString type=ui->le_type->text();
    float qer=ui->le_qer->text().toFloat();
    float cout=ui->le_cout->text().toFloat();
    Fournisseur F(id,type,qer,cout);
    bool test=F.ajouter();
    QMessageBox msgBox;
    if (test)
    {
        msgBox.setText("Ajouté avec succès.");
        ui->tableView->setModel(F.afficher());
        ui->tableView_2->setModel(F.afficher_his());
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Echec de l'ajout.");
        msgBox.exec();
    }
}

void MainWindow::on_pb_supp_clicked()
{
    Fournisseur F1;
    F1.setid(ui->le_id_supp->text().toInt());
    bool test=F1.supprimer(F1.getid());
    QMessageBox msgBox;
    if (test)
    {
        msgBox.setText("Supprimé avec succès.");
        ui->tableView->setModel(F.afficher());
        ui->tableView_2->setModel(F.afficher_his());
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Echec de la suppression.");
        msgBox.exec();
    }
}

void MainWindow::on_pb_modifier_clicked()
{
     int id=ui->le_id_2->text().toInt();
     QString type=ui->le_type_2->text();
     float qer=ui->le_qer_2->text().toFloat();
     float cout=ui->le_cout_2->text().toFloat();
     Fournisseur F(id,type,qer,cout);
     bool test=F.modifier();
     QMessageBox msgBox;
     if(test)
     {
         msgBox.setText("Modification réussie.");
         ui->tableView->setModel(F.afficher());
         ui->tableView_2->setModel(F.afficher_his());
     }
     else
         msgBox.setText("Échec de la modification");
}





void MainWindow::on_ajouter_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
ui->tableView->setModel(F.afficher());

}

void MainWindow::on_modifier_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->tableView->setModel(F.afficher());
}

void MainWindow::on_afficher_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->tableView->setModel(F.afficher());
}

void MainWindow::on_recherche_textChanged(const QString &arg1)
{
    QString chaine=ui->recherche->text();
    int  id=0;
    QString   type="";
    float  qer=0;
    float  cout=0;
    Fournisseur F(id,type,qer,cout);

    if(chaine !="")
            {
             ui->tableView->setModel(F.rechercher(chaine));
            }
            else
            {
                QString trieOption=ui->recherche->text();
                ui->tableView->setModel(F.rechercher(trieOption));
            }

}

void MainWindow::on_comboBox_tri_currentTextChanged(const QString &arg1)
{
    QString chaine=ui->comboBox_tri->currentText();
    int  id=0;
    QString   type="";
    float  qer=0;
    float  cout=0;
    Fournisseur F(id,type,qer,cout);


 ui->tableView->setModel(F.trier(chaine));


}

void MainWindow::on_pushButton_clicked()
{
    QPdfWriter pdf("C:/Users/ASUS/Documents/Projet C++/Projet_CPP/2A14_smart_electric_charging_station/Pdf/pdf.pdf");

           QPainter painter(&pdf);
           int i = 4100;
          const QImage image(":/new/icons/icons/logo.png");
          const QImage image1(":/new/icons/icons/cap.png");
                       const QPoint imageCoordinates(155,0);
                       const QPoint imageCoordinates1(6000 ,12000);
                       int width1 = 1600;
                       int height1 = 1600;
                       int width2 = 3000;
                       int height2 = 1600;



                       QImage img=image.scaled(width1,height1);
                       QImage img1=image1.scaled(width2,height2);

                       painter.drawImage(imageCoordinates, img );
                       painter.drawImage(imageCoordinates1, img1 );


                  QColor dateColor(0x4a5bcf);
                  painter.setPen(dateColor);

                  painter.setFont(QFont("Montserrat SemiBold", 11));
                  QDate cd = QDate::currentDate();
                  painter.drawText(8400,250,cd.toString("Ariana"));
                  painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                  QColor titleColor(0x341763);
                  painter.setPen(titleColor);
                  painter.setFont(QFont("Montserrat SemiBold", 25));

                  painter.drawText(3000,2700,"Liste des fournisseurs");

                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  //painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3300,9400,500);

                  painter.setFont(QFont("Montserrat SemiBold", 10));

                  painter.drawText(500,3600,"ID");
                  painter.drawText(2000,3600,"Type");
                  painter.drawText(3300,3600,"Quantité");
                  painter.drawText(7500,3600,"Cout");
                  painter.setFont(QFont("Montserrat", 10));
                  painter.drawRect(100,3300,9400,5000);

                  QSqlQuery query;
                  query.prepare("select * from fournisseur");
                  query.exec();
                  int y=4300;

                  while (query.next())
                  {
                      painter.drawLine(100,y,9490,y);

                      // painter.drawLine(3300, y - 500, 3300, y + 500);

                      y+=500;
                      painter.drawText(500,i,query.value(0).toString());
                       painter.drawLine(100,y,9490,y);

                      painter.drawText(2000,i,query.value(1).toString());
                       painter.drawLine(100,y,9490,y);

                      painter.drawText(3300,i,query.value(3).toString());
                       painter.drawLine(100,y,9490,y);
                      painter.drawText(4500,i,query.value(4).toString());

                      painter.drawText(7500,i,query.value(2).toString());

                     i = i + 500;


                  }
                  QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                  QObject::tr("PDF Enregistré!.\n" "Appuyez sur Cancel pour quitter."), QMessageBox::Cancel);
                  QDesktopServices::openUrl(QUrl("file:///Pdf/pdf.pdf"));
                  QString fileName = "C:/Users/ASUS/Documents/Projet C++/Projet_CPP/2A14_smart_electric_charging_station/Pdf/pdf.pdf";

                  QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

void MainWindow::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_BTn_refresh_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                         model->setQuery("select * from fournisseur where Cout < 100 ");
                         float surface=model->rowCount();
                         model->setQuery("select * from fournisseur where Cout  between 100 and 250 ");
                         float surface1=model->rowCount();
                         model->setQuery("select * from fournisseur where Cout >250 ");
                         float surface2=model->rowCount();
                         float total=surface+surface1+surface2;
                         QString a=QString(" - que 100 \t"+QString::number((surface*100)/total,'f',2)+"%" );
                         QString b=QString("entre 100 et 250 \t"+QString::number((surface1*100)/total,'f',2)+"%" );
                         QString c=QString(" + que 250 \t"+QString::number((surface2*100)/total,'f',2)+"%" );
                         QPieSeries *series = new QPieSeries();
                         series->append(a,surface);
                         series->append(b,surface1);
                         series->append(c,surface2);
                 if (surface!=0)
                 {QPieSlice *slice = series->slices().at(0);
                  slice->setLabelVisible();
                  slice->setPen(QPen());}
                 if ( surface1!=0)
                 {
                          // Add label, explode and define brush for 2nd slice
                          QPieSlice *slice1 = series->slices().at(1);
                          //slice1->setExploded();
                          slice1->setLabelVisible();
                 }
                 if(surface2!=0)
                 {
                          // Add labels to rest of slices
                          QPieSlice *slice6 = series->slices().at(2);
                          //slice1->setExploded();
                          slice6->setLabelVisible();
                 }

                         QChart *chart = new QChart();

                             chart->addSeries(series);
                             chart->setTitle("");
                            chart->setBackgroundVisible(false);



                         chart->setVisible(true);
                         chart->legend()->setAlignment(Qt::AlignBottom);


                         QChartView *chartView = new QChartView(chart);

                         chartView->setRenderHint(QPainter::Antialiasing);
                         QPalette pal = qApp->palette();

                         chartView->setMaximumWidth(731);
                         chartView->setMaximumHeight(381);
                         chartView->setMinimumWidth(411);
                         chartView->setMinimumHeight(251);
                         chartView->setParent(ui->lineEdit_stat);
                         chartView->show();
}

void MainWindow::on_le_id_supp_clicked()
{
    int i;
            QModelIndex index=ui->tableView->currentIndex();
        i=index.row();
        QModelIndex in=index.sibling(i,0);

        int val=ui->tableView->model()->data(in).toInt();

            bool test=F.supprimer(val);
            if (test)
            {
                QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Suppression réussie.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);
            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("Suppression échouée.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);

    ui->tableView->setModel(F.afficher());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tableView_2->setModel(F.afficher_his());
}
void  MainWindow::browse()
{
    files.clear();
   QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_2->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("karim.bensalah@esprit.tn",ui->mail_pass_2->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailsent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("karim.bensalah@esprit.tn", ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText(), files );
    else
        smtp->sendMail("karim.bensalah@esprit.tn", ui->rcpt_2->text() , ui->subject_2->text(),ui->msg_2->toPlainText());
}
void   MainWindow::mailsent(QString status)
{

    if(status == "Message sent")
    { QMessageBox::information(nullptr, QObject::tr("Votre Mail est ouvert."),
                               QObject::tr("Mail envoyé.\n"
                                           "Appuyez sur Cancel pour quitter."), QMessageBox::Cancel);
    }
    ui->rcpt_2->clear();
    ui->subject_2->clear();
    ui->file_2->clear();
    ui->msg_2->clear();
    ui->mail_pass_2->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_onArduino_clicked()
{
    QString d=A.read_from_arduino().right(6);
            qDebug() << d.right(6);
    if (d!="0"){
    QSqlQuery query;
    query.prepare("INSERT INTO PARKING (voitures)"
                  "VALUES (:voitures)");
    query.bindValue(":voitures", d);
    query.exec();
    }
}
