#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "QMessageBox"
#include "Arduino.h"
#include <fournisseur.h>
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
    void on_pb_ajouter_clicked();

    void on_pb_supp_clicked();

    void on_pb_modifier_clicked();

    void on_ajouter_4_clicked();

    void on_modifier_4_clicked();

    void on_afficher_4_clicked();

    void on_recherche_textChanged(const QString &arg1);

    void on_comboBox_tri_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_BTn_refresh_clicked();

    void on_le_id_supp_clicked();

    void on_pushButton_3_clicked();
    void  browse();
    void sendMail();
    void   mailsent(QString );

    void on_pushButton_4_clicked();

    void on_onArduino_clicked();

private:
    Ui::MainWindow *ui;
    Fournisseur F;
    QStringList files;
      Arduino A;
};
#endif // MAINWINDOW_H
