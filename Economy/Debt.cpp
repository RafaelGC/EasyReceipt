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

bool Debt::operator==(const Debt &debt) const
{
    return (this->creditor==debt.getCreditor() && this->debtor==debt.getDebtor());
}

bool Debt::isSwappedVersionOf(const Debt &debt) const
{
    return (this->debtor==debt.getCreditor() && this->creditor==debt.getDebtor());
}

bool Debt::compatibleWith(const Debt &debt) const
{
    return ((*this)==debt || this->isSwappedVersionOf(debt));
}

void Debt::swapIfNeeded()
{
    if (amount<0){
        QString tmp = this->creditor;
        creditor = debtor;
        debtor = tmp;
        amount*=-1;
    }

}

void Debt::operator+=(const Debt &debt)
{
    if ((*this)==debt){
        this->setAmount(this->getAmount()+debt.getAmount());
    }
    else if (this->isSwappedVersionOf(debt)){
        this->setAmount(this->getAmount()-debt.getAmount());
    }
    this->swapIfNeeded();
}

QString Debt::getDebtor() const
{
    return debtor;
}

QString Debt::getCreditor() const
{
    return creditor;
}

float Debt::getAmount(bool rounded) const
{
    if (rounded){
        return round(amount*100)/100;
    }
    return amount;
}
