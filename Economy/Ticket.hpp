#ifndef TICKET_HPP
#define TICKET_HPP

#include <string>
#include <vector>
#include <QDebug>

#include "Product.hpp"
#include "Debt.hpp"

class Ticket
{
private:
    std::vector<Product*>products;
    std::vector<std::pair<QString,float>>payers;
    QString ticketName;
public:
    enum{MONEY_DOES_NOT_MATCH,SUCCESS};
    Ticket(QString tiketName);
    ~Ticket();

    void setName(const QString &name);
    QString getName();

    float getTotalCost(bool rounded=false) const;

    Product* addProduct(float price, std::vector<QString>buyers);
    Product* addProduct(Product product);

    void removeProduct(const Product* product);
    float getPurchasePriceOf(QString buyer, bool rounded=false) const;

    void clear();

    const Product* productAt(int index) const;
    unsigned int countProducts() const;

    void addPayer(QString name, float amount);
    std::vector<Debt> computePayout(int *message) const;
    std::vector<std::pair<QString,float>> getPayers() const;
    float getAmountPayedBy(QString name) const;

    QStringList getBuyers() const;

};

#endif // TICKET_HPP
