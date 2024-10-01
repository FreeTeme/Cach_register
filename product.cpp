#include "Product.h"

Product::Product() : name(""), category(""), price(0.0),quality(1){}

Product::Product(const QString &name, const QString &category, double price)
    : name(name), category(category), price(price),quality(1) {}

Product::~Product() {}

QString Product::getName() const {
    return name;
}

void Product::setName(const QString &value) {
    name = value;
}

QString Product::getCategory() const {
    return category;
}

void Product::setCategory(const QString &value) {
    category = value;
}

double Product::getPrice() const {
    return price;
}

void Product::setPrice(double value) {
    price = value;
}


int Product::getQuality() const {
    return quality;
}

void Product::setQuality(int value) {
    quality = value;
}
