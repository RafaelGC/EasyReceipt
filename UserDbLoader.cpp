#include "UserDbLoader.hpp"

UserDbLoader::UserDbLoader(QWidget *parent, UserContainer *userContainer, UserDbInterface *userDb, UsersManagerDialog *usersManagerDialog)
{
    this->parent = parent;
    this->userContainer = userContainer;
    this->userDb = userDb;
    this->usersManagerDialog = usersManagerDialog;
}

void UserDbLoader::load()
{
    if (!connect()) return;

    QStringList userNames = constructList();
    loadListIntoContainer(userNames);
    close();
}

bool UserDbLoader::connect()
{
    if (!userDb->connect()){
        QMessageBox::critical(parent,"Error","No se pudo establecer la conexión con la base de datos local.");
        return false;
    }
    return true;
}

QStringList UserDbLoader::constructList()
{
    bool success;
    QStringList userList = userDb->queryUsers(&success);
    if (!success){
        QMessageBox::critical(parent,QObject::tr("Error"),QObject::tr("Error al cargar los usuarios."));
    }

    return userList;
}

void UserDbLoader::loadListIntoContainer(const QStringList &userList)
{
    for (auto it = userList.begin(); it!=userList.end(); ++it){
        userContainer->addUser(User(*it,false));
        usersManagerDialog->addUserToList(*it);
    }
}

void UserDbLoader::close()
{
    userDb->close();
}
