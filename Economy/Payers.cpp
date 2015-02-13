#include "Payers.hpp"

Payers::Payers()
{
}

void Payers::clear()
{
    payers.clear();
}

unsigned int Payers::countPayers() const
{
    return payers.size();
}

void Payers::removePayer(const QString &name)
{
    for (auto it=payers.begin(); it!=payers.end(); ++it){
        if ((*it).getName()==name){
            payers.erase(it);
            return;
        }
    }
}

void Payers::setPayer(const Payer &payer)
{
    for (auto it=payers.begin(); it!=payers.end(); ++it){
        if (((const Payer)(*it))==payer){
            (*it).setAmount(payer.getAmount());
            return;
        }
    }
}

float Payers::payedBy(const QString &name) const
{
    for (auto it=payers.begin(); it!=payers.end(); ++it){
        if ((*it).getName()==name){
            return (*it).getAmount();
        }
    }
    return 0.f;
}

float Payers::totalPayed() const
{
    float counter = 0.f;
    for (auto it=payers.begin(); it!=payers.end(); ++it){
        counter += (*it).getAmount();
    }
    return counter;
}
