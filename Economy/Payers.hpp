#ifndef PAYERS_HPP
#define PAYERS_HPP

#include "Economy/Payer.hpp"

#include <vector>

class Payers
{
private:
    std::vector<Payer> payers;
public:
    Payers();

    void clear();
    unsigned int countPayers() const;

    void removePayer(const QString & name);
    //Para actualizar y añadir pagadores:
    void setPayer(const Payer &payer);

    float payedBy(const QString &name) const;
    float totalPayed() const;
};

#endif // PAYERS_HPP
