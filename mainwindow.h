#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "services.h"
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











    void on_ajouter_clicked();

    void on_afficher_clicked();

    void on_chercher_textChanged();

    void on_trier_currentTextChanged();

    void on_pdf_clicked();

    void on_stat_clicked();

    void on_calendrier_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_supp_clicked();

    void on_modif_clicked();

    void on_pb_ajouter_2_clicked();

    void on_modifier_clicked();

    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
    Services S;
};
#endif // MAINWINDOW_H
