#ifndef DIALOG_ADMIN_H
#define DIALOG_ADMIN_H

#include <QDialog>
#include<QStandardItemModel>
#include<menu.h>
#include <QInputDialog>
#include <QCryptographicHash>
#include<QMessageBox>

namespace Ui {
class Dialog_admin;
}

class Dialog_admin : public QDialog
{
    Q_OBJECT

public:
    enum buttom {
        history,
        check,
        SuperAdmin
    };
    explicit Dialog_admin(buttom Buttom,QWidget *parent = nullptr);
    ~Dialog_admin();

private slots:


    void on_back_buttom_clicked();
    void on_add_buttom_clicked();
    bool chec(const QString &login,const QString &password);
    void save(const QString &login, const QString &hashedPassword);
    void on_tableView_clicked(const QModelIndex &index);
    void remove(int row);
    void loadReviews();

private:
    buttom Buttom;
    Ui::Dialog_admin *ui;
    QStandardItemModel *model;
    QString filename;


};

#endif // DIALOG_ADMIN_H
