#ifndef CART_H
#define CART_H

#include<menu.h>
#include<product.h>
#include<productmanager.h>
#include<carts.h>


#include <QDialog>
#include<QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

namespace Ui {
class cart;
}

class cart : public QDialog
{
    Q_OBJECT

public:
    explicit cart(QWidget *parent = nullptr);
    ~cart();
    void add(Product product);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void calculateTotal();
    void showCart(QTableView *view);
    void on_tableView_clicked(const QModelIndex &index);
    QList<Product> getProducts();
    double getTotal();


private:
    Ui::cart *ui;
    ProductManager productcart;
};

#endif // CART_H
