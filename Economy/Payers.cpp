#include "Payers.hpp"

Payers::Payers()
{
}

void Payers::clear()
{
    UserAmountCollection::clear();
}

unsigned int Payers::countPayers() const
{
    return UserAmountCollection::count();
}

void Payers::removePayer(const QString &name)
{
    UserAmountCollection::remove(name);
}

void Payers::setPayer(const UserAmount &payer)
{
    UserAmountCollection::set(payer);
}

float Payers::payedBy(const QString &name) const
{
    return UserAmountCollection::amountOf(name);
}

float Payers::totalPayed() const
{
    return UserAmountCollection::total();
}

UserAmount &Payers::operator[](int index)
{
    return UserAmountCollection::operator [](index);
}

bool Payers::isPayer(const QString &name) const
{
    return UserAmountCollection::contains(name);
}
