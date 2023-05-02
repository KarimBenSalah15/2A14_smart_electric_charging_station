#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "services.h"
#include <QIntValidator>
#include <QMessageBox>
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->le_Num_Service->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_Num_Service_2->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_prix_2->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_prix->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_duree->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_duree_2->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_disponibilite->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
   ui->le_disponibilite_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
   ui->le_type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));
   ui->le_type_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+"), this));




ui->tableView->setModel(S.afficher());



ui->trier->addItem("par défaut");
ui->trier->addItem("par Num_Service");
ui->trier->addItem("par prix");
ui->trier->addItem("par duree");
ui->trier->addItem("par type");
ui->trier->addItem("par disponibilite");

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pb_ajouter_clicked()
{
    int Num_Service=ui->le_Num_Service->text().toInt();
    QString type=ui->le_type->text();
    int prix=ui->le_prix->text().toInt();
    int duree=ui->le_duree->text().toInt();
    QString disponibilite=ui->le_disponibilite->text();
    QDate date_S=ui->dateEdit->date();

  Services S(Num_Service,type,prix,duree,disponibilite,date_S);
  bool test=S.ajouter();
  QMessageBox msgBox;

  if(test)
  { msgBox.setText("Ajout avec succès");
      ui->tableView->setModel(S.afficher());
      msgBox.exec();
}
  else
  {    msgBox.setText("Echec de l'ajout");
       msgBox.exec();}
}








void MainWindow::on_ajouter_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_afficher_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
     ui->tableView->setModel(S.afficher());
}

void MainWindow::on_chercher_textChanged()
{
    QString chaine=ui->chercher->text();

        int  Num_Service=0;
         int   prix=0;

          QString  type="";
          int duree=0;
         QString   disponibilite="";
         QDate date_S;

           Services S(Num_Service,type,prix,duree,disponibilite,date_S);

            if(chaine !="")
            {
            ui->tableView->setModel(S.rechercher(chaine));
            }
            else
            {
                QString trieOption=ui->chercher->text();
                ui->tableView->setModel(S.rechercher(trieOption));

            }
}

void MainWindow::on_trier_currentTextChanged()
{
    QString chaine=ui->trier->currentText();

    int  Num_Service=0;
     int   prix=0;
      QString  type="";
      int duree=0;
     QString   disponibilite="";
QDate date_S;
       Services S(Num_Service,type,prix,duree,disponibilite,date_S);



                ui->tableView->setModel(S.trier(chaine));
}

void MainWindow::on_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/Selim/Desktop/travail/2A14/Projet C++/PremierAppp/pdf/pdf.pdf");

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

                      painter.drawText(3000,2700,"Liste des services");

                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Time New Roman", 15));
                      //painter.drawRect(100,100,9400,2500);
                      painter.drawRect(100,3300,9400,500);

                      painter.setFont(QFont("Montserrat SemiBold", 10));

                      painter.drawText(500,3600,"Num_Service");
                      painter.drawText(2000,3600,"type");
                      painter.drawText(3300,3600,"prix");
                      painter.drawText(5000,3600,"duree");
                      painter.drawText(7500,3600,"disponibilite");
                      painter.setFont(QFont("Montserrat", 10));
                      painter.drawRect(100,3300,9400,5000);

                      QSqlQuery query;
                      query.prepare("select * from service");
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
                      QString fileName = "C:/Users/Selim/Desktop/travail/2A14/Projet C++/PremierAppp/pdf/pdf.pdf";

                      QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

void MainWindow::on_stat_clicked()
{
ui->stackedWidget->setCurrentIndex(2);
        QSqlQueryModel * model= new QSqlQueryModel();
                             model->setQuery("select * from service where prix < 100 ");
                             float prix=model->rowCount();
                             model->setQuery("select * from service where prix  between 100 and 250 ");
                             float prix1=model->rowCount();
                             model->setQuery("select * from service where prix >250 ");
                             float prix2=model->rowCount();
                             float total=prix+prix1+prix2;
                             QString a=QString(" [-100] \t"+QString::number((prix*100)/total,'f',2)+"%" );
                             QString b=QString(" [100-250] \t"+QString::number((prix1*100)/total,'f',2)+"%" );
                             QString c=QString("[+250] \t"+QString::number((prix2*100)/total,'f',2)+"%" );
                             QPieSeries *series = new QPieSeries();
                             series->append(a,prix);
                             series->append(b,prix1);
                             series->append(c,prix2);
                     if (prix!=0)
                     {QPieSlice *slice = series->slices().at(0);
                      slice->setLabelVisible();
                      slice->setPen(QPen());}
                     if ( prix1!=0)
                     {
                              // Add label, explode and define brush for 2nd slice
                              QPieSlice *slice1 = series->slices().at(1);
                              slice1->setExploded();
                              slice1->setLabelVisible();
                     }
                     if(prix2!=0)
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
                             chartView->setParent(ui->stats);
                             chartView->show();
}

void MainWindow::on_calendrier_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();


        QSqlQuery qry;
        qry.prepare("select * from service where num_service='"+val+"' " );


        if(qry.exec())
        {
            while(qry.next())
            {
                ui->le_Num_Service->setText(qry.value(0).toString());
                ui->le_prix->setText(qry.value(1).toString());
                ui->le_type->setText(qry.value(2).toString());
                ui->dateEdit->setDate(qry.value(3).toDate());
                ui->le_duree->setText(qry.value(4).toString());
                ui->le_disponibilite->setText(qry.value(5).toString());


            }
}
}

void MainWindow::on_supp_clicked()
{
    int i;
            QModelIndex index=ui->tableView->currentIndex();
        i=index.row();
        QModelIndex in=index.sibling(i,0);

        int val=ui->tableView->model()->data(in).toInt();

            bool test=S.supprimer(val);
    QMessageBox msgBox;

        if (test)
          { msgBox.setText("Suppresion réussie.");

        msgBox.exec();
        }

        else
          { msgBox.setText("Echec de la suppresion");
            msgBox.exec();}

ui->tableView->setModel(S.afficher());
}

void MainWindow::on_modif_clicked()
{
ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pb_ajouter_2_clicked()
{
    int i;
            QModelIndex index=ui->tableView->currentIndex();
        i=index.row();
        QModelIndex in=index.sibling(i,0);
        int val=ui->tableView->model()->data(in).toInt();

    int Num_Service=ui->le_Num_Service_2->text().toInt();
    QString type=ui->le_type_2->text();
    int prix=ui->le_prix_2->text().toInt();
    int duree=ui->le_duree_2->text().toInt();
    QString disponibilite=ui->le_disponibilite_2->text();
    QDate date_S=ui->dateEdit_2->date();


  Services S(Num_Service,type,prix,duree,disponibilite,date_S);
  bool test=S.modifier(val);
  QMessageBox msgBox;

  if(test)
  { msgBox.setText("modification effectuee avec succès");
      ui->tableView->setModel(S.afficher());

       msgBox.exec();
}
  else
  {msgBox.setText("Echec de la modification");
        msgBox.exec();}

}



void MainWindow::on_calendarWidget_selectionChanged()
{
    QString x=ui->calendarWidget->selectedDate().toString();

        ui->lineEdit->setText(x);
        QDate x1=ui->calendarWidget->selectedDate();
       ui->tableView_2->setModel(S.afficher_calendar(x1));
}
