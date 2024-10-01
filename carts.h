#ifndef CARTS_H
#define CARTS_H

#include<cart.h>
#include <QDialog>


namespace Ui {
class Carts;
}

class Carts : public QDialog
{
    Q_OBJECT

public:
    explicit Carts(QWidget *parent = nullptr);
    ~Carts();

private slots:
    void on_back_Buttom_clicked();


    void on_exit_buttom_clicked();

private:
    Ui::Carts *ui;
};

#endif // CARTS_H
