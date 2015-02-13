#ifndef PAYER_HPP
#define PAYER_HPP

#include <QString>

class Payer
{
private:
    QString name;
    float amount;
public:
    Payer(const QString &name, float amount);

    QString getName() const;
    void setName(const QString &value);

    float getAmount() const;
    void setAmount(float value);

    bool operator==(const Payer &payer) const;
};

#endif // PAYER_HPP
