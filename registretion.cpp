#include "registretion.h"
#include "ui_registretion.h"

registretion::registretion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registretion)
{
    ui->setupUi(this);
}

registretion::~registretion()
{
    delete ui;
}

QJsonObject registretion::readJson(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Не удалось открыть файл.");
        return QJsonObject();
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    return doc.object();
}

bool registretion::chec(const QString &login,const QString &password)
{
    QFile file("admins.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Не удалось открыть файл.");
        return false;
    }
    QString hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray usersArray = doc.array();

    for (int i = 0; i < usersArray.size(); ++i) {
        QJsonObject userObj = usersArray[i].toObject();
        if (userObj["1"].toString() == login  ) {
            return true;
        }
    }

    return false;
}




void registretion::on_enter_button_clicked()
{
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    if(chec(login, password)){
        QMessageBox::information(this, "Вход выполнен", "Вы успешно вошли в систему!");
        try {
            hide();
            menu *main = new menu(menu::Admin);
            main->show();
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
        }
    }else if(login=="super"||password=="super"){
        QMessageBox::information(this, "Вход выполнен", "Вы успешно вошли в систему!");
        try {
            hide();
            menu *main = new menu(menu::Super_Admin);
            main->show();
        } catch (const std::exception &e) {
            QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
        }
    }else {
        QMessageBox::warning(this, "Ошибка входа", "Неверный логин или пароль!");
    }
}

void registretion::on_back_button_clicked(){
    try {
        hide();
        MainWindow *main = new MainWindow();
        main->show();
    } catch (const std::exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", "Страница не найдена!");
    }
}
