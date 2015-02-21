#include "UserAmountCollection.hpp"

UserAmountCollection::UserAmountCollection()
{
}

void UserAmountCollection::clear()
{
    usersAmount.clear();
}

unsigned int UserAmountCollection::count() const
{
    return usersAmount.size();
}

void UserAmountCollection::remove(const QString &name)
{
    for (auto it=usersAmount.begin(); it!=usersAmount.end(); ++it){
        if ((*it).getName()==name){
            usersAmount.erase(it);
            return;
        }
    }
}

void UserAmountCollection::set(const UserAmount &user)
{
    for (auto it=usersAmount.begin(); it!=usersAmount.end(); ++it){
        if (((const UserAmount)(*it))==user){
            (*it).setAmount(user.getAmount());
            return;
        }
    }

    //Si llegamos a este punto de ejecución es porque no re ha
    //encontrado al usuario, así que se añade.
    usersAmount.push_back(user);
}

float UserAmountCollection::amountOf(const QString &name) const
{
    for (auto it=usersAmount.begin(); it!=usersAmount.end(); ++it){
        if ((*it).getName()==name){
            return (*it).getAmount();
        }
    }
    return 0.f;
}

float UserAmountCollection::total() const
{
    float counter = 0.f;
    for (auto it=usersAmount.begin(); it!=usersAmount.end(); ++it){
        counter += (*it).getAmount();
    }
    return counter;
}

bool UserAmountCollection::contains(const QString &name) const
{
    for (auto it = usersAmount.begin(); it != usersAmount.end(); ++it){
        if ((*it).getName()==name){
            return true;
        }
    }
    return false;
}

UserAmount &UserAmountCollection::operator[](int index)
{
    return usersAmount[index];
}
