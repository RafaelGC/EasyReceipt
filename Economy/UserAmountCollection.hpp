#ifndef USERAMOUNTCOLLECTION_HPP
#define USERAMOUNTCOLLECTION_HPP

#include <QString>
#include <vector>

#include "UserAmount.hpp"

class UserAmountCollection
{
protected:
    std::vector<UserAmount> usersAmount;
    UserAmountCollection();

    void clear();
    unsigned int count() const;

    void remove(const QString & name);
    //Para actualizar y añadir pagadores:
    void set(const UserAmount &user);

    float amountOf(const QString &name) const;
    float total() const;

    bool contains(const QString &name) const;

    UserAmount& operator[](int index);
};

#endif // USERAMOUNTCOLLECTION_HPP
