#include "User.hpp"

User::User()
{
    this->name = "";
}

User::User(const QString &name, bool removable){
    this->name = name;
    this->removable = removable;
}

/*****************************
 *SETTERS
 *****************************/
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
const QString& User::getName() const{
    return name;
}

bool User::isRemovable() const
{
    return removable;
}
