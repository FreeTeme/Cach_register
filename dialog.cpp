#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString text = ui->textEdit->toPlainText();
    saveToJson(text);
    QMessageBox::information( this,"Успех", "Сообщение отправлено!");
    hide();
}

void Dialog::saveToJson(const QString &review){
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeString = currentDateTime.toString(Qt::ISODate);

    QJsonObject reviewObj;
    reviewObj["1"] = currentDateTimeString;
    reviewObj["2"] = review;

    QJsonArray reviewsArray;
    QFile file("reviews.json");
    if (file.open(QIODevice::ReadWrite)) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        reviewsArray = jsonDoc.array();
        reviewsArray.append(reviewObj);
        jsonDoc.setArray(reviewsArray);
        file.seek(0);
        file.write(jsonDoc.toJson());
        file.close();
    } else {
        QMessageBox::critical( this,"Ошибка", "Не удалось открыть файл!");
    }
}

void Dialog::on_pushButton_2_clicked()
{
    hide();
}

