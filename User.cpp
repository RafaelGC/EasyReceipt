#include "User.hpp"

User::User()
{
    this->name = "";
    this->debt = 0;
}

User::User(const QString &name, bool removable){
    this->name = name;
    this->debt = 0;
    this->removable = removable;
}

void User::increaseDebt(float increment){
    debt+=increment;
}

/*****************************
 *SETTERS
 *****************************/

void User::setDebt(float debt){
    this->debt = debt;
}

void User::setName(QString name){
    this->name = name;
}


void User::setRemovable(bool removable)
{
    this->removable = removable;
}

/*****************************
 *GETTERS
 *****************************/

float User::getDebt() const{
    return debt;
}

const QString& User::getName() const{
    return name;
}

bool User::isRemovable() const
{
    return removable;
}
