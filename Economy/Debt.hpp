#ifndef DEBT_HPP
#define DEBT_HPP

#include <QString>

class Debt
{
private:
    QString debtor, creditor;
    float amount;
public:
    Debt();
    Debt(QString debtor, float amount, QString creditor);

    void setDebtor(QString name);
    void setCreditor(QString name);
    void setAmount(float amount);

    QString getDebtor() const;
    QString getCreditor() const;
    float getAmount(bool rounded=false) const;

    bool operator==(const Debt &debt) const;
    bool isSwapped(const Debt &debt) const;
    void swapIfNeeded();
};

#endif // DEBT_HPP
