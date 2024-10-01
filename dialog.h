#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QMessageBox>
#include<QString>
#include<QDateTime>
#include<QJsonDocument>
#include<QIODevice>
#include<QFile>
#include<QJsonObject>
#include<QJsonArray>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void saveToJson(const QString &review);
private:
    Ui::Dialog *ui;


};

#endif // DIALOG_H
