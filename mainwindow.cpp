#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_admin_button_clicked()
{
    try {
        hide();
        registretion *main = new registretion();
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }

}


void MainWindow::on_person_button_clicked()
{
    try {
        hide();
        menu *Menu = new menu(menu::User);
        Menu->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}

