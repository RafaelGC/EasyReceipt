#ifndef USERCONTAINER_HPP
#define USERCONTAINER_HPP

#include <QString>
#include <QVector>

#include "User.hpp"

class UserContainer
{
private:
    std::vector<User>users;
public:
    UserContainer();

    User* addUser(const QString &userName);
    User* addUser(const User &user);
    User* getUserNameStartWith(const QString&userName);
    int userExists(const QString &userName) const;
    User* userAt(int index);
    void deleteUser(const QString&userName);
    void deleteUser(int index);
    unsigned int size() const;
    void cleanUpVolatileUsersIfPossible();
    float getTotalDebt();
};

#endif // USERCONTAINER_HPP
