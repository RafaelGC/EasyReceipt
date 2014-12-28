#include "Debt.hpp"

Debt::Debt()
{
    amount = 0;
}

Debt::Debt(QString debtor, float amount, QString creditor)
{
    setDebtor(debtor);
    setCreditor(creditor);
    setAmount(amount);
}

void Debt::setDebtor(QString name)
{
    this->debtor = name;
}

void Debt::setCreditor(QString name)
{
    this->creditor = name;
}

void Debt::setAmount(float amount)
{
    this->amount = amount;
}

QString Debt::getDebtor()
{
    return debtor;
}

QString Debt::getCreditor()
{
    return creditor;
}

float Debt::getAmount(bool rounded)
{
    if (rounded){
        return round(amount*100)/100;
    }
    return amount;
}
