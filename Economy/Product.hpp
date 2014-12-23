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

    bool buyedBy(QString name);
    float getPrice();
    void addBuyer(QString name);
    void removeBuyer(QString name);
    float getPayout();
};

#endif // PRODUCT_HPP
