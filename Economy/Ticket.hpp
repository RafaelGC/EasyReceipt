#ifndef TICKET_HPP
#define TICKET_HPP

#include <string>
#include <vector>

#include "Product.hpp"

class Ticket
{
private:
    std::vector<Product>products;
public:
    Ticket();

    float getTotalCost();
    void addProduct(Product product);
    float getPurchasePriceOf(QString buyer);

};

#endif // TICKET_HPP
