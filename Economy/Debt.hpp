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

    //Métodos de comparación.
    bool operator==(const Debt &debt) const;
    bool isSwappedVersionOf(const Debt &debt) const;
    bool compatibleWith(const Debt &debt) const;

    void swapIfNeeded();

    void operator+=(const Debt &debt);
};

#endif // DEBT_HPP
