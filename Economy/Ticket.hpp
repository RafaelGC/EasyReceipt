#ifndef TICKET_HPP
#define TICKET_HPP

#include <string>
#include <vector>
#include <QDebug>

#include "Product.hpp"

class Ticket
{
private:
    std::vector<Product*>products;
public:
    Ticket();
    ~Ticket();

    float getTotalCost() const;
    Product* addProduct(float price, std::vector<QString>buyers);
    Product* addProduct(Product product);
    void removeProduct(Product* product);
    float getPurchasePriceOf(QString buyer) const;
    void clear();
    const Product* productAt(int index) const;
    unsigned int countProducts() const;

};

#endif // TICKET_HPP
