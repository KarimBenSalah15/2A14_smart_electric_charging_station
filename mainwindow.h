#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "ui_mainwindow.h"
#include"voiture.h"
#include<QMessageBox>
#include<QDebug>
#include<QMainWindow>
#include<QIntValidator>
#include<QTableView>
#include<QSqlQueryModel>
#include<QItemSelectionModel>
#include<dialog_statist.h>
#include"arduino.h"
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_chercher_button_clicked();




    void on_radioButton_croissant_clicked();

    void on_radioButton_dcroissant_clicked();

    void on_export_pdf_clicked();

    void on_pushButton_2_clicked();



    void on_btn_export_clicked();

    void on_qrcodegen_clicked();

    void on_tab_client_activated(const QModelIndex &index);

    void on_browseBtn_clicked();

    void on_qrcodegen_2_clicked();



    void update_labelclient();


    void on_B_produit_Historique_2_clicked();


    void on_update_labelclient_clicked();

    void on_chercher_button_aaaa_clicked();

private:
    Ui::MainWindow *ui;
    VOITURE v;
    Dialog_statist *s;
    QStringList files;

      QString mnomemp="localhost";
      quint16 mport=3333;


    QByteArray data; // variable contenant les données reçues
     Arduino A; // objet temporaire



};
#endif // MAINWINDOW_H
