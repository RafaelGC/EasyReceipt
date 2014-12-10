#ifndef HISTORYELEMENT_HPP
#define HISTORYELEMENT_HPP

#include <QString>

class HistoryElement
{
private:
    QString names, cost;
public:
    HistoryElement();
    HistoryElement(const QString &names, const QString &cost);

    QString getNames() const;
    QString getCost() const;

    void setNames(const QString&names);
    void setCost(const QString&cost);
};

#endif // HISTORYELEMENT_HPP
