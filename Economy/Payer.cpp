#include "Payer.hpp"


QString Payer::getName() const
{
    return name;
}

void Payer::setName(const QString &value)
{
    name = value;
}

float Payer::getAmount() const
{
    return amount;
}

void Payer::setAmount(float value)
{
    amount = value;
}

bool Payer::operator==(const Payer &payer) const
{
    return payer.getName()==name;
}
Payer::Payer(const QString &name, float amount)
{
    this->name = name;
    this->amount = amount;
}
