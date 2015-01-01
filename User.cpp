#include "User.hpp"

User::User()
{
    this->name = "";
}

User::User(const QString &name, bool _volatile){
    this->name = name;
    this->_volatile = _volatile;
}

/*****************************
 *SETTERS
 *****************************/
void User::setName(QString name){
    this->name = name;
}


void User::setVolatile(bool _volatile)
{
    this->_volatile = _volatile;
}

/*****************************
 *GETTERS
 *****************************/
const QString& User::getName() const{
    return name;
}

bool User::isVolatile() const
{
    return _volatile;
}
