#ifndef REGISTRETION_H
#define REGISTRETION_H

#include<mainwindow.h>
#include<menu.h>

#include <QDialog>
#include<QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class registretion;
}

class registretion : public QDialog
{
    Q_OBJECT

public:
    explicit registretion(QWidget *parent = nullptr);
    ~registretion();

private slots:
    void on_back_button_clicked();
    void on_enter_button_clicked();
    QJsonObject readJson(const QString &filename);
    bool chec(const QString &login, const QString &password);

private:
    Ui::registretion *ui;
};

#endif // REGISTRETION_H
