#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <vector>
#include <string>

#include <QString>

class Product
{
private:
    std::vector<QString>buyers;
    float price;
public:
    Product();
    Product(float price, std::vector<QString>buyers);
    Product(float price);

    bool buyedBy(QString name) const;
    float getPrice() const;
    void addBuyer(QString name);
    void removeBuyer(QString name);
    float getPayout() const;
    QString getStringBuyers() const;
};

#endif // PRODUCT_HPP
