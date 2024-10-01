#include "dialog_admin.h"
#include "ui_dialog_admin.h"

Dialog_admin::Dialog_admin(buttom Buttom,QWidget *parent)
    : QDialog(parent), Buttom(Buttom)
    , ui(new Ui::Dialog_admin)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);

    ui->add_buttom->hide();
    if(Buttom==history){
        filename="reviews.json";
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else if(Buttom==check){
        filename="history.json";
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else if(Buttom==SuperAdmin){
        ui->add_buttom->show();
        filename="admins.json";
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    }
    loadReviews();
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


}

Dialog_admin::~Dialog_admin()
{
    delete ui;
}

void Dialog_admin::loadReviews() {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        QJsonArray reviewsArray = jsonDoc.array();

        for (int i = 0; i < reviewsArray.size(); ++i) {
            QJsonObject reviewObj = reviewsArray[i].toObject();
            QString date = reviewObj["1"].toString();
            QString review = reviewObj["2"].toString();

            QStandardItem *dateItem = new QStandardItem(date);
            QStandardItem *reviewItem = new QStandardItem(review);

            model->appendRow({dateItem, reviewItem});
        }

        file.close();
    } else {
        qDebug() << "Не удалось открыть файл:" << filename;
        qDebug() << "Ошибка:" << file.errorString();
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл!");
    }
}






void Dialog_admin::on_back_buttom_clicked()
{
    hide();
}



void Dialog_admin::on_add_buttom_clicked()
{
    bool ok;
    QString login = QInputDialog::getText(this, tr("Добавить админа"),
                                          tr("Логин:"), QLineEdit::Normal,
                                          "", &ok);
    if (ok && !login.isEmpty()){
        QString password = QInputDialog::getText(this, tr("Добавить админа"),
                                                 tr("Пароль:"), QLineEdit::Password,
                                                 "", &ok);
        if (ok && !password.isEmpty()){
            if(chec(login, password)){
                QMessageBox::warning(this, "Ошибка", "Такой логин уже существует!");
            } else {

                QString hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
                save(login, hashed);
                QStandardItem *dateItem = new QStandardItem(login);
                QStandardItem *reviewItem = new QStandardItem(hashed);
                model->appendRow({dateItem,reviewItem});
            }
        }
    }
}

bool Dialog_admin::chec(const QString &login,const QString &password)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Не удалось открыть файл.");
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray usersArray = doc.array();

    for (int i = 0; i < usersArray.size(); ++i) {
        QJsonObject userObj = usersArray[i].toObject();
        if (userObj["login"].toString() == login ||userObj["password"].toString() == password ) {
            return true;
        }
    }

    return false;
}

void Dialog_admin::save(const QString &login, const QString &hashed)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning("Не удалось открыть файл.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray usersArray = doc.array();


    QJsonObject newAdmin;
    newAdmin["1"] = login;
    newAdmin["2"] = hashed;


    usersArray.append(newAdmin);

    doc.setArray(usersArray);
    file.seek(0);
    file.write(doc.toJson());
    file.close();
}







void Dialog_admin::on_tableView_clicked(const QModelIndex &index)
{
    if(Buttom==SuperAdmin){
        QMessageBox msgBox;
        msgBox.setText("Вы действительно хотите УДАЛИТЬ этот элемент?");
        QAbstractButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole);
        QAbstractButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);

        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            int row=index.row();
            remove(row);
        }
    }

}


void Dialog_admin::remove(int row) {
    model->removeRow(row);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Не удалось открыть файл.");
        return;
    }
    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray users = doc.array();
    users.removeAt(row);

    doc.setArray(users);
    file.close();
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Не удалось открыть файл.");
        return;
    }
    file.write(doc.toJson());
    file.close();
}





