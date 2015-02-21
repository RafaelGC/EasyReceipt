#include "UserAmount.hpp"


QString UserAmount::getName() const
{
    return name;
}

void UserAmount::setName(const QString &value)
{
    name = value;
}

float UserAmount::getAmount() const
{
    return amount;
}

void UserAmount::setAmount(float value)
{
    amount = value;
}

bool UserAmount::operator==(const UserAmount &payer) const
{
    return payer.getName()==name;
}
UserAmount::UserAmount(const QString &name, float amount)
{
    this->name = name;
    this->amount = amount;
}
