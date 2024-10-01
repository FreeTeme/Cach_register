#ifndef PRODUCT_H
#define PRODUCT_H


#include <QString>

class Product {
public:
    Product();
    Product(const QString &name, const QString &category, double price);
    ~Product();

    QString getName() const;
    void setName(const QString &value);

    QString getCategory() const;
    void setCategory(const QString &value);

    double getPrice() const;
    void setPrice(double value);

    int getQuality() const;
    void setQuality(int value);

private:
    QString name;
    QString category;
    double price;
    int quality;
};




#endif // PRODUCT_H
