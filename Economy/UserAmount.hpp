#ifndef PAYER_HPP
#define PAYER_HPP

#include <QString>
/**
 * @brief La clase UserAmount representa a un cierto usuario y una cantidad de dinero
 * vinculada a él.
 */
class UserAmount
{
private:
    QString name;
    float amount;
public:
    UserAmount(const QString &name, float amount);

    QString getName() const;
    void setName(const QString &value);

    float getAmount() const;
    void setAmount(float value);

    bool operator==(const UserAmount &payer) const;
};

#endif // PAYER_HPP
