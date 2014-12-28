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

    QString getDebtor();
    QString getCreditor();
    float getAmount(bool rounded=false);
};

#endif // DEBT_HPP
