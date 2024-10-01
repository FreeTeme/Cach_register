#include "add.h"
#include "ui_add.h"
#include<product.h>

Add::Add(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add)
    , productManager("product.json")
{
    ui->setupUi(this);
}

Add::~Add()
{
    delete ui;
}

void Add::on_pushButton_clicked()
{
    QString name=ui->nameEdit->text();
    QString category=ui->categoryEdit->text();
    QString coastString=ui->coastEdit->text();

    if (name.isEmpty() || category.isEmpty() || coastString.isEmpty()) {
        QMessageBox::critical(nullptr, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    bool ok;
    double coast = coastString.toDouble(&ok);

    if (!ok || coast<0) {
        QMessageBox::critical(nullptr, "Ошибка", "Стоимость должна быть числом!");
        return;
    }

    if (productManager.find(name)) {
        QMessageBox::critical(nullptr, "Ошибка", "Продукт с таким именем уже существует!");
        return;
    }

    add=Product(name,category,coast);
    productManager.add(add);

    try {
        hide();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}


void Add::on_pushButton_2_clicked()
{
    hide();

}

void Add::setName( const QString &name){
    ui->nameEdit->setText(name);
}

void Add::setCategory( const QString &name){
    ui->categoryEdit->setText(name);
}

void Add::setPrice( const QString &name){
    ui->coastEdit->setText(name);
}

QString Add::getName() const { return ui->nameEdit->text(); }
QString Add::getCategory() const { return ui->categoryEdit->text(); }
double Add::getPrice() const { return ui->coastEdit->text().toDouble(); }


