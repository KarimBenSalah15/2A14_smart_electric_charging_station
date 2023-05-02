#ifndef DIALOG_STATIST_H
#define DIALOG_STATIST_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


QT_CHARTS_USE_NAMESPACE
namespace Ui {
class Dialog_statist;
}

class Dialog_statist : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog_statist(QWidget *parent = nullptr);
    ~Dialog_statist();
    QChartView *chartView ;
    void choix_bar();
    void choix_pie();

private:
    Ui::Dialog_statist *ui;
};
#endif // DIALOG_STATIST_H






