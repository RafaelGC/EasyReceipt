#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <vector>
#include <string>

class Product
{
private:
    std::vector<std::string>buyers;
    float price;
public:
    Product();
    Product(float price, std::vector<std::string>buyers);
    Product(float price);

    bool buyedBy(std::string name);
    float getPrice();
    void addBuyer(std::string name);
    void removeBuyer(std::string name);
};

#endif // PRODUCT_HPP
