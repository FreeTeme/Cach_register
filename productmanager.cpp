#include "productmanager.h"

ProductManager::ProductManager(const QString &filename):filename(filename) {}

void ProductManager::add(Product &product){

    loadFromJson();
    products.push_back(product);
    saveToJson();
}

void ProductManager::loadFromJson() {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = file.readAll();
        QJsonDocument parsedJson = QJsonDocument::fromJson(jsonData);
        QJsonArray productsArray = parsedJson.array();

        products.clear();
        for (const QJsonValue &productValue : productsArray) {
            QJsonObject productObj = productValue.toObject();
            Product product;
            product.setName(productObj["name"].toString());
            product.setCategory(productObj["category"].toString());
            product.setPrice(productObj["price"].toDouble());
            product.setQuality(productObj["quality"].toInt());
            products.append(product);
        }
    }
}

void ProductManager::saveToJson() {
    QJsonArray productsArray;
    for (const Product &product : products) {
        QJsonObject productObj;
        productObj["name"] = product.getName();
        productObj["category"] = product.getCategory();
        productObj["price"] = product.getPrice();
        productObj["quality"] = product.getQuality();
        productsArray.append(productObj);
    }
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument jsonDoc(productsArray);
        file.write(jsonDoc.toJson());
        file.close();
    } else {
        qDebug() << "Не удалось открыть файл:" << filename;
        qDebug() << "Ошибка:" << file.errorString();
    }
}





void ProductManager::reverse(){
    int n=products.size();
    for (int i=0;i<n/2;++i){
        Product temp=products[i];
        products[i]=products[n-i-1];
        products[n-i-1]=temp;
    }
}

void ProductManager::sort_alp(bool revers=false){
    int gap=products.size();
    bool swaped= true;
    while(gap>1||swaped){
        if(gap>1){
            gap=gap*10/13;
        }
        swaped=false;
        for(int i=0;i<products.size()-gap;++i){
            if(products[i].getName()>products[i+gap].getName()){
                std::swap(products[i],products[i+gap]);
                swaped=true;
            }
        }
    }
    if(revers){
        reverse();
    }
}

void ProductManager::sort_sum(bool reverse=false){
    quickSort(0, products.size()-1);
    if(reverse){
        this->reverse();
    }
}

void ProductManager::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

int ProductManager::partition(int low, int high) {
    Product pivot = products[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (products[j].getPrice() < pivot.getPrice()) {
            i++;
            swap(&products[i], &products[j]);
        }
    }
    swap(&products[i + 1], &products[high]);
    return (i + 1);
}

void ProductManager::swap(Product *a, Product *b) {
    Product t = *a;
    *a = *b;
    *b = t;
}




void ProductManager::show(QTableView *view) {
    QStandardItemModel *model = new QStandardItemModel(products.size(), 3);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Имя")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Категория")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Цена")));

    for(int i = 0; i < products.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(products[i].getName()));
        model->setItem(i, 1, new QStandardItem(products[i].getCategory()));
        model->setItem(i, 2, new QStandardItem(QString::number(products[i].getPrice())));
    }

    view->setModel(model);
}

bool ProductManager::find(const QString &name) {
    for (const Product &product : products) {
        if (product.getName() == name) {
            return true;
        }
    }
    return false;
}



void ProductManager::remove(int index){
    products.removeAt(index);
    saveToJson();
}


QList<Product> ProductManager::bin_search(double binary){
    sort_sum(false);
    QList<Product> sorted = products;
    int left = 0;
    int right = sorted.size() - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (sorted[mid].getPrice() <= binary) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    QList<Product> result = sorted.mid(0, left);
    return result;
}

QJsonArray ProductManager::toJsonArray() {
    QJsonArray jsonArray;
    for (const Product &product : products) {
        QJsonObject productObj;
        productObj["name"] = product.getName();
        productObj["category"] = product.getCategory();
        productObj["price"] = product.getPrice();
        productObj["quality"] = product.getQuality();
        jsonArray.append(productObj);
    }
    return jsonArray;
}

/*void ProductManager::merge(){

    QList<Product>left=
    QList<Product>right=
}*/
