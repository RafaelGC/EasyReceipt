#ifndef USERDBLOADER_HPP
#define USERDBLOADER_HPP

#include <QMessageBox>

#include "Dialogs/UsersManagerDialog.hpp"
#include "Persistence/UserDbInterface.hpp"
#include "UserContainer.hpp"

class UserDbLoader
{
private:
    QWidget *parent;
    UserContainer *userContainer;
    UserDbInterface *userDb;
    UsersManagerDialog *usersManagerDialog;

    bool connect();
    QStringList constructList();
    void loadListIntoContainer(const QStringList &userList);
    void close();
public:
    UserDbLoader(QWidget *parent,UserContainer *userContainer, UserDbInterface *userDb, UsersManagerDialog *usersManagerDialog);
    void load();
};

#endif // USERDBLOADER_HPP
