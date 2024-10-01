#include "menu.h"
#include "ui_menu.h"

menu::menu(Users users,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::menu)
    , users(users)
    , productManager("product.json")
{
    ui->setupUi(this);

    productManager.loadFromJson();
    productManager.show(ui->tableView);

    QSet<QString> categories;
    for ( Product product : productManager.getProducts()) {
        categories.insert(product.getCategory());
    }
    ui->filterBox->addItems(categories.values());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    if(users==Admin){
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->super_admin_buttom->hide();
    }else if(users==User){
        ui->super_admin_buttom->hide();
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->history_button->hide();
        ui->check_buttom->hide();
        ui->add_button->hide();
    }else if(users==Super_Admin){
        ui->pushButton->hide();
        ui->pushButton_2->hide();
    }
    ui->edit_button->hide();
    ui->check_buttom->hide();

}

menu::~menu()
{
    delete ui;
}

void menu::on_back_button_clicked()
{
    try {
        hide();
        MainWindow *main = new MainWindow();
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}

void menu::on_pushButton_2_clicked()
{
    try {
        hide();
        cart *main = new cart();
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}

void menu::on_pushButton_clicked()
{
    try{
        Dialog *main = new Dialog();
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}

void menu::on_sortBox_currentIndexChanged(int index)
{
    updateTableView();
}

void menu::on_add_button_clicked()
{
    Add *addDialog = new Add(this);

    if (addDialog->exec() == QDialog::Accepted) {
        double price = addDialog->getPrice();
        if (price >= 0) {
            Product newProduct;
            newProduct.setName(addDialog->getName());
            newProduct.setCategory(addDialog->getCategory());
            newProduct.setPrice(price);
            productManager.add(newProduct);
        } else {
            qDebug() << "Ошибка: Цена должна быть больше или равна нулю.";
        }
    }
    updateTableView();
    delete addDialog;
}



void menu::on_filterBox_currentTextChanged(const QString &category) {
    updateTableView();
}

void menu::on_check_buttom_clicked()
{
    try {
        Dialog_admin *main = new Dialog_admin(Dialog_admin::check);
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}

void menu::on_history_button_clicked()
{
    try {
        Dialog_admin *main = new Dialog_admin(Dialog_admin::history);
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}

void menu::on_super_admin_buttom_clicked()
{
    try {
        Dialog_admin *main = new Dialog_admin(Dialog_admin::SuperAdmin);
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}

void menu::on_searchEdit_textChanged(const QString &arg1)
{
    updateTableView();
}

void menu::updateTableView() {
    productManager.loadFromJson();
    QString searchText = ui->searchEdit->text();
    QString categoryFilter = ui->filterBox->currentText();
    int sortIndex = ui->sortBox->currentIndex();
    switch (sortIndex) {
    case 1:
        productManager.sort_alp(false);
        break;
    case 2:
        productManager.sort_sum(false);
        break;
    case 3:
        productManager.sort_sum(true);
        break;
    case 4:
        productManager.reverse();
        break;
    case 5:
        productManager.sort_alp(true);
        break;
    }
    productManager.show(ui->tableView);
    for (int i = 0; i < ui->tableView->model()->rowCount(); ++i) {
        QModelIndex indexName = ui->tableView->model()->index(i, 0);
        QModelIndex indexCategory = ui->tableView->model()->index(i, 1);
        QString cellValueName = indexName.data().toString();
        QString cellValueCategory = indexCategory.data().toString();

        bool hide = !cellValueName.contains(searchText, Qt::CaseInsensitive);
        if (categoryFilter != "Все") {
            hide = hide || (cellValueCategory != categoryFilter);
        }

        ui->tableView->setRowHidden(i, hide);
    }
}

void menu::on_tableView_clicked(const QModelIndex &index)
{
    if (users == User) {
        QMessageBox msgBox;
        msgBox.setText("Вы действительно хотите добавить этот элемент?");
        QAbstractButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        QAbstractButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);

        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            int row=index.row();
            cart Cart;
            Cart.add(productManager.getProducts()[row]);
        }
    }else if(users==Admin||users==Super_Admin){
        ui->edit_button->show();
        QMessageBox msgBox;
        msgBox.setText("Вы действительно хотите УДАЛИТЬ этот элемент?");
        QAbstractButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        QAbstractButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);

        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {

            int row=index.row();
            productManager.remove(row);
            updateTableView();
        }
    }
}

void menu::on_search_buttom_clicked()
{
    QString text=ui->binary_Edit->text();
    if (text.isEmpty()) {
        productManager.loadFromJson();
        productManager.show(ui->tableView);
    }else{
        bool ok;
        double binary=text.toDouble(&ok);

        if(ok){
            bynary_search(binary);
        }else {
            QMessageBox::warning(this, "Invalid Input", "Пожалуйста вводите только цифры.");
        }
    }


}

void menu::bynary_search(double binary){
    QList<Product> searchResults = productManager.bin_search(binary);
    QStandardItemModel *model = new QStandardItemModel(searchResults.size(), 3);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Имя")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Категория")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Цена (руб.)")));

    for(int i = 0; i < searchResults.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(searchResults[i].getName()));
        model->setItem(i, 1, new QStandardItem(searchResults[i].getCategory()));
        model->setItem(i, 2, new QStandardItem(QString::number(searchResults[i].getPrice())));
    }

    ui->tableView->setModel(model);
}

void menu::on_edit_button_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    int row = index.row();
    Add *editDialog = new Add(this);
    Product select=productManager.getProducts()[row];
    editDialog->setName(select.getName());
    editDialog->setCategory(select.getCategory());
    editDialog->setPrice(QString::number(select.getPrice()));
    if (editDialog->exec() == QDialog::Accepted) {
        double price = editDialog->getPrice();
        if(price>=0){
            select.setName(editDialog->getName());
            select.setCategory(editDialog->getCategory());
            select.setPrice(editDialog->getPrice());
            productManager.add(select);
            productManager.remove(row);
        }
    }
    updateTableView();
    delete editDialog;
    ui->edit_button->hide();

}




