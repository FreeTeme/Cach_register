#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include<product.h>

#include<QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QSortFilterProxyModel>
#include<QMessageBox>
#include<QObject>
#include <QStandardItemModel>
#include<QTableView>


class ProductManager {
private:
    QVector<Product> products;
    QString filename;
    

public:
    ProductManager(const QString &filename);
    QVector<Product>& getProducts() {
        return products;}
    void remove(int index);
    void add(Product &product);
    void show(QTableView *view);
    void reverse();
    void sort_alp(bool reverse);
    void sort_sum(bool reverse);

    void quickSort(int low, int high);
    void swap(Product *a, Product *b);
    bool find(const QString &name);
    int partition(int low, int high);

    void getJson();
    void setJson();
    QList<Product> bin_search(double binary);
    void loadFromJson();
    void saveToJson();
    QJsonArray toJsonArray();
    void clear();
};



#endif // PRODUCTMANAGER_H
