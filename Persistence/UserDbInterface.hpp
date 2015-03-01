#ifndef USERDBINTERFACE_HPP
#define USERDBINTERFACE_HPP

#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include <QDebug>
#include <QSqlError>

#include "Config.hpp"

class UserDbInterface
{
private:
    QSqlDatabase db;
public:
    explicit UserDbInterface();
    ~UserDbInterface();
    bool connect();
    void close();

    QStringList queryUsers(bool *ok=nullptr);
    bool saveUser(const QString &userName);
    bool deleteUser(const QString &userName);

};

#endif // USERDBINTERFACE_HPP
