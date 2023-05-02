#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "empolyee.h"
#include <QMainWindow>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QLineEdit>
#include <QMainWindow>
#include<QRegExp>
#include <QSettings>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include "dialog.h"
#include "smtp.h"
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();
    //void on_push_load_clicked();

    void on_pb_supprimer_clicked();


    void on_pb_modifier_clicked();
    //void on_pushButton_9_clicked();
    //void on_pb_modifier_2_clicked();
  void on_pb_tri_clicked();
 void on_pb_rech_mod_clicked();
  void on_pdf_clicked();
  void on_pb_tri_desc_clicked();



  void on_search_textChanged(const QString &arg1);

  void on_pb_stats_clicked();
  void sendMail();
    void mailSent(QString);
    void browse();

    void on_export_excel_clicked();

private:

  QSortFilterProxyModel *proxy;
    Ui::MainWindow *ui;
    empolyee P ;
    Dialog *s;
 QStringList files;

};

#endif // MAINWINDOW_H

