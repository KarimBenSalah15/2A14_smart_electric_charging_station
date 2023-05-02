#ifndef DIALOG_H
#define DIALOG_H
#include "services.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setServices(Services s);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
