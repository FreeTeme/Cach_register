#include "carts.h"
#include "ui_carts.h"

Carts::Carts(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Carts)
{
    ui->setupUi(this);
}

Carts::~Carts()
{
    delete ui;
}

void Carts::on_back_Buttom_clicked()
{
    try {
        hide();
        cart *main = new cart();
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}


void Carts::on_exit_buttom_clicked()
{
    QString cvv=ui->cvv_edit->text();
    QString cart=ui->carts_edit->text();
    bool ok;
    double coast = cvv.toDouble(&ok);

   /*if (name.isEmpty() || category.isEmpty() || coastString.isEmpty()) {
        QMessageBox::critical(nullptr, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }*/

    if (!ok || coast<0 ) {
        QMessageBox::critical(nullptr, "Ошибка", "Данные введены не корректно!");
        return;
    }else{
        try {
            hide();
            MainWindow *main = new MainWindow();
            main->show();
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
        }
    }
}
