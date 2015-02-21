#ifndef TICKET_HPP
#define TICKET_HPP

#include <string>
#include <vector>
#include <QDebug>

#include "Product.hpp"
#include "Debt.hpp"
#include "Payers.hpp"
#include "UserAmount.hpp"

class Ticket
{
private:
    std::vector<Product*>products;
    Payers payers;
    QString ticketName;
public:
    Ticket(QString tiketName);
    ~Ticket();

    void setName(const QString &name);
    QString getName() const;

    float getTotalCost(bool rounded=false) const;
    float getPurchasePriceOf(QString buyer, bool rounded=false) const;

    Product* addProduct(Product product);
    void removeProduct(const Product* product);
    const Product* productAt(int index) const;
    unsigned int countProducts() const;

    void clear();


    Payers* getPayers();

    /**
     * @brief Genera la lista de todos los compradores.
     * @return Nombres de todos los compradores.
     */
    QStringList getBuyers() const;

};

#endif // TICKET_HPP
