#include "mainwindow.h"
#include"exportexcelobject.h"
#include"empolyee.h"
#include<QIntValidator>
#include <QMainWindow>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QLineEdit>
#include<QIntValidator>
#include <QMessageBox>
#include<QRegExp>
#include <QPdfWriter>
#include <QPainter>
//#include <QPrinter>
//#include <QPrintDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{

    ui->setupUi(this);
ui->ID_EMPLOYE->setValidator(new QIntValidator(0, 9999999, this));



ui->tab_empolyee->setModel(P.afficher());
ui->tab_empolyee->setSortingEnabled(true);//tri



proxy = new QSortFilterProxyModel();

//definir la source (tableau original)
proxy->setSourceModel(P.afficher());

//pour la recherche
proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
proxy->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
//remplissage tableau avec le masque
ui->tab_empolyee->setModel(proxy);

}

MainWindow::~MainWindow()
{
    delete ui;
}
////////////////////////////




void MainWindow::on_pb_ajouter_clicked()
{
    int ID_EMPLOYE=ui->ID_EMPLOYE->text().toInt();
    QString NOM=ui->nom->text();
    QString PRENOM= ui->PRENOM->text();
    QString TYPE=ui->TYPE->text();
    int NBR_HEURE=ui->NBR_HEURE->text().toInt();
    int SALAIRE=ui->SALAIRE->text().toInt();


       /*ui->NOM->setMaxLength(20);
       ui->PRENOM->setMaxLength(20);*/
    //************mailllll
        // Formater le corps du message avec les valeurs saisies
        QString message = QString("Bonjour,\n\n" // Ajouter ici le mot "Bonjour" au début du mail
                                   "Le dossier avec l'ID %1 a été ajouté avec succès.\n"
                                   "NOM : %2\n"
                                   "PRENOM : %3\n"
                                   "TYPE: %4\n"
                                   "NBRE HEURE : %5\n"
                                   "SALAIRE: %4\n\n"
                                  "Cordialement,") // Ajouter ici le mot "Cordialement" à la fin du mail
                            .arg(ID_EMPLOYE)
                            .arg(NOM)
                            .arg(PRENOM)
                            .arg(TYPE)
                            .arg(NBR_HEURE)
                .arg(SALAIRE)  ;

        Smtp* smtp = new Smtp("benhadjyahia.mehdi@esprit.tn", "211JMT9273", "smtp.gmail.com", 465);

        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtp->sendMail("benhadjyahia.mehdi@esprit.tn", "benhadjyahia.mehdi@esprit.tn","DOSSIER employe", message);

        //*************

    empolyee P  ( ID_EMPLOYE , NOM, PRENOM,TYPE, NBR_HEURE, SALAIRE) ;


bool test=P.ajouter();
if(test)
 {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                               QObject::tr("ajout successful.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
  ui->tab_empolyee->setModel(P.afficher());
           }
               else
                   QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                               QObject::tr("ajout failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tab_empolyee->setModel(P.afficher());
}
void MainWindow::on_pb_supprimer_clicked()
     {
         empolyee P ;

             int ID_EMPLOYE = ui->le_ID_C_supprimer->text().toInt();
             bool test=P.supprimer(ID_EMPLOYE);
             if (test)
             {
                 QMessageBox::information(nullptr,QObject::tr("OK"),
                         QObject::tr("Suppression effectuée\n"
                                     "Click Cancel non to exit.") , QMessageBox :: Cancel);
                ui->tab_empolyee->setModel((P.afficher()));//refrersh
             }
             else
                 QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                                       QObject::tr("Suppression non effectuée.\n"
                                                   "Click Cancel to exit."),QMessageBox::Cancel);
             ui->tab_empolyee->setModel((P.afficher()));
}
void MainWindow::on_pb_modifier_clicked()
{
    int ID_EMPLOYE=ui->id2->text().toInt();
    QString NOM=ui->nom2->text();
    QString PRENOM=ui->tel2->text();
    QString TYPE=ui->TYPE2->text();
    int NBR_HEURE=ui->NBR_HEURE2->text().toInt();
    int SALAIRE=ui->SALAIRE2->text().toInt();
     empolyee P  ( ID_EMPLOYE , NOM, PRENOM,TYPE, NBR_HEURE, SALAIRE) ;
    bool test=P.modifier(ID_EMPLOYE);
        if(test)
        { ui->tab_empolyee->setModel(P.afficher());
     QMessageBox::information(nullptr, QObject::tr("modification avec succes"),
                 QObject::tr("Modification effectuée.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("erreur de modification"),
                    QObject::tr(" erreur.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pb_tri_clicked()
{
ui->tab_empolyee->setModel(P.tri_asc());


}

//pdf : vous trouver le fichier dans le dossier build
void MainWindow::on_pdf_clicked()
{

    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_empolyee->model()->rowCount();
                const int columnCount =ui->tab_empolyee->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1>Liste des Evenements</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_empolyee->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_empolyee->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_empolyee->isColumnHidden(column)) {
                                   QString data = ui->tab_empolyee->model()->data(ui->tab_empolyee->model()->index(row, column)).toString().simplified();
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


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("mypdffile.pdf");
        document->print(&printer);

}



void MainWindow::on_pb_rech_mod_clicked()
{
  /*  QString id1=ui->ID_EMPLOYE->currentText();

     ui->tab_empolyee->setModel(P.rechercher(id1));
     ui->ID_EMPLOYE->clear();
   */



}
void MainWindow::on_pb_tri_desc_clicked()
{
    ui->tab_empolyee->setModel(P.tri_desc());

}

void MainWindow::on_search_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);
}

void MainWindow::on_pb_stats_clicked()
{
    s=new Dialog();

      s->setWindowTitle("statistique ");
      s->choix_pie();
      s->show();
}
//mailing
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

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("benhadjyahia.mehdi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("benhadjyahia.mehdi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("benhadjyahia.mehdi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void MainWindow::on_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                            tr("Excel Files (*.xls)"));
            if (fileName.isEmpty())
                return;

            ExportExcelObject obj(fileName, "mydata", ui->tab_empolyee);

            //colums to export
            obj.addField(0, "ID", "char(20)");
            obj.addField(1, "NOM", "char(20)");
            obj.addField(2, "PRENOM", "char(20)");
            obj.addField(3, "TYPE", "int");
            obj.addField(4, "NBR_HEURE", "char(20)");
            obj.addField(4, "SALAIRE", "char(20)");



            int retVal = obj.export2Excel();
            if( retVal > 0)
            {
                QMessageBox::information(this, tr("Done"),
                                         QString(tr("%1 records exported!")).arg(retVal)
                                         );
            }
}
