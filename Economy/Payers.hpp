#ifndef PAYERS_HPP
#define PAYERS_HPP

#include "Economy/UserAmount.hpp"
#include "Economy/UserAmountCollection.hpp"

#include <vector>

class Payers : protected UserAmountCollection
{
public:
    Payers();

    void clear();
    unsigned int countPayers() const;

    void removePayer(const QString & name);
    void setPayer(const UserAmount &payer);

    float payedBy(const QString &name) const;
    float totalPayed() const;

    UserAmount& operator[](int index);

    bool isPayer(const QString &name) const;
};

#endif // PAYERS_HPP
