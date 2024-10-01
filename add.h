#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include<productmanager.h>
#include<product.h>
#include<menu.h>


namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();

    void setName( const QString &name);
    void setCategory( const QString &name);
    void setPrice( const QString &name);
    QString getName ()const;
    QString getCategory ()const ;
    double getPrice ()const;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::Add *ui;
    ProductManager productManager;
    Product add;
};

#endif // ADD_H
