#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(100, 9999999, this));
    ui->tab_fournisseur->setModel(F.afficher());
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
        ui->tab_fournisseur->setModel(F.afficher());
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
        ui->tab_fournisseur->setModel(F.afficher());
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
         ui->tab_fournisseur->setModel(F.afficher());
     }
     else
         msgBox.setText("Échec de la modification");
}
