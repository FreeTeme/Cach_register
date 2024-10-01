#include "cart.h"
#include "ui_cart.h"

cart::cart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cart)
    , productcart("cart.json")
{
    ui->setupUi(this);
    productcart.loadFromJson();
    productcart.sort_alp(false);
    showCart(ui->tableView);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    calculateTotal();
}

cart::~cart()
{
    delete ui;
}

void cart::on_pushButton_clicked()
{
    try {
        hide();
        menu *main = new menu(menu::User);
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}

void cart::on_pushButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Выберите способ оплаты");
    QAbstractButton* pButtonYes = msgBox.addButton("Картой", QMessageBox::YesRole);
    QAbstractButton* pButtonNo = msgBox.addButton("Наличными", QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        try {
            hide();
            Carts *main = new Carts();
            main->show();
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
        }
        QJsonArray historyArray;
        QJsonObject historyObject;
        historyObject["date"] = QDateTime::currentDateTime().toString();
        historyObject["products"] = productcart.toJsonArray();
        historyArray.append(historyObject);
        QFile historyFile("history.json");
        if (historyFile.open(QIODevice::WriteOnly)) {
            historyFile.write(QJsonDocument(historyArray).toJson());
            historyFile.close();
        }
        QFile receiptFile("receipt.txt");
        if (receiptFile.open(QIODevice::WriteOnly)) {
            QTextStream out(&receiptFile);
            out << "Чек от " << QDateTime::currentDateTime().toString() << "\n";
            foreach (Product it, productcart.getProducts()) {
                out << it.getName() << " - " << it.getPrice() << " x " << it.getQuality() << " = " << it.getPrice()*it.getQuality() << "\n";
            }
            out << "Общая стоимость (руб.): " << ui->totallabel->text() << "\n";
            receiptFile.close();
        }
        productcart.clear();
        productcart.saveToJson();
        showCart(ui->tableView);
        calculateTotal();
    } else if (msgBox.clickedButton()==pButtonNo) {

        QJsonArray historyArray;
        QJsonObject historyObject;
        historyObject["date"] = QDateTime::currentDateTime().toString();
        historyObject["products"] = productcart.toJsonArray();
        historyArray.append(historyObject);
        QFile historyFile("history.json");
        if (historyFile.open(QIODevice::WriteOnly)) {
            historyFile.write(QJsonDocument(historyArray).toJson());
            historyFile.close();
        }
        QFile receiptFile("receipt.txt");
        if (receiptFile.open(QIODevice::WriteOnly)) {
            QTextStream out(&receiptFile);
            out << "Чек от " << QDateTime::currentDateTime().toString() << "\n";
            foreach (Product it, productcart.getProducts()) {
                out << it.getName() << " - " << it.getPrice() << " x " << it.getQuality() << " = " << it.getPrice()*it.getQuality() << "\n";
            }
            out << "Общая стоимость: " << ui->totallabel->text() << "\n";
            receiptFile.close();
        }
        productcart.clear();
        productcart.saveToJson();
        showCart(ui->tableView);
        calculateTotal();
        try {
            hide();
            MainWindow *main = new MainWindow();
            main->show();
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
        }

    }
}


void cart::add( Product product){
    for(int i=0;i<productcart.getProducts().size();++i) {
        if(productcart.getProducts()[i].getName() == product.getName()) {
            Product exit=productcart.getProducts()[i];
            productcart.remove(i);
            exit.setQuality(exit.getQuality() + 1);
            productcart.add(exit);
            productcart.saveToJson();
            calculateTotal();
            productcart.show(ui->tableView);
            return;
        }
    }
    productcart.add(product);
    productcart.saveToJson();
    calculateTotal();
}

void cart::calculateTotal() {
    double total = 0.0;
    foreach (Product it, productcart.getProducts()) {
        total+=it.getPrice()*it.getQuality();
    }
    ui->totallabel->setText(QString::number(total));
}

void cart::showCart(QTableView *view) {
    QList<Product> products = productcart.getProducts();
    QStandardItemModel *model = new QStandardItemModel(products.size(), 4);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Имя")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Категория")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Цена (руб.)")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Количество")));

    for(int i = 0; i < products.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(products[i].getName()));
        model->setItem(i, 1, new QStandardItem(products[i].getCategory()));
        model->setItem(i, 2, new QStandardItem(QString::number(products[i].getPrice())));
        model->setItem(i, 3, new QStandardItem(QString::number(products[i].getQuality())));
    }

    view->setModel(model);
}








void cart::on_tableView_clicked(const QModelIndex &index)
{
    if (!index.isValid() || index.row() >= productcart.getProducts().size()) {
        return;
    }

    bool ok;
    QString quantityStr = QInputDialog::getText(this, tr("Изменить количество"),
                                                tr("Введите новое количество товара:"), QLineEdit::Normal,
                                                "", &ok);
    if (ok && !quantityStr.isEmpty()) {
        double quantity = quantityStr.toDouble();

        if (quantity < 0) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Количество не может быть меньше нуля."));
            return;
        }

        if (quantity == 0) {
            QMessageBox msgBox;
            msgBox.setText("Вы действительно хотите удалить товар?");
            QAbstractButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
            QAbstractButton* pButtonNo = msgBox.addButton("Отмена", QMessageBox::NoRole);
            msgBox.exec();
            if (msgBox.clickedButton() == pButtonYes) {
                productcart.remove(index.row());
            } else if(msgBox.clickedButton() == pButtonNo) {
                return;
            }
        } else {
            productcart.getProducts()[index.row()].setQuality(static_cast<int>(quantity));
        }

        productcart.saveToJson();
        showCart(ui->tableView);
        calculateTotal();
    }
}

void ProductManager::clear() {
    products.clear();
    saveToJson();
}

QList<Product> cart::getProducts() {
    return productcart.getProducts();
}

double cart::getTotal() {
    return ui->totallabel->text().toDouble();
}


