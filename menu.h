#ifndef MENU_H
#define MENU_H

#include<mainwindow.h>
#include<cart.h>
#include<productmanager.h>
#include<dialog.h>
#include<add.h>
#include<dialog_admin.h>

#include <QDialog>
#include<QStandardItemModel>
#include<QTableView>
#include<QRegularExpression>
#include<QStandardItem>
#include<QAbstractItemModel>
#include<QModelIndex>

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    enum Users{
        Admin,
        User,
        Super_Admin
    };
    explicit menu(Users users,QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_back_button_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_sortBox_currentIndexChanged(int index);
    void on_add_button_clicked();
    void on_filterBox_currentTextChanged(const QString &arg1);
    void on_check_buttom_clicked();
    void on_history_button_clicked();
    void on_super_admin_buttom_clicked();
    void on_searchEdit_textChanged(const QString &arg1);
    void updateTableView();
    void on_tableView_clicked(const QModelIndex &index);
    void on_search_buttom_clicked();
    void bynary_search(double binary);
    void on_edit_button_clicked();


private:
    Ui::menu *ui;
    Users users;
    ProductManager productManager;
    QStandardItemModel *model;



};

#endif // MENU_H
