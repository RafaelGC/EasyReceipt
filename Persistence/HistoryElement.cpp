#include "HistoryElement.hpp"

HistoryElement::HistoryElement()
{
    this->cost = "";
    this->names = "";
}

HistoryElement::HistoryElement(const QString &names, const QString &cost)
{
    this->names = names;
    this->cost = cost;
}

QString HistoryElement::getNames() const
{
    return this->names;
}

QString HistoryElement::getCost() const
{
    return this->cost;
}

void HistoryElement::setNames(const QString &names)
{
    this->names = names;
}

void HistoryElement::setCost(const QString &cost)
{
    this->cost = cost;
}
