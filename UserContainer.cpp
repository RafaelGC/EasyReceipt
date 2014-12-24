#include "UserContainer.hpp"

UserContainer::UserContainer()
{
}

User* UserContainer::addUser(const QString &userName){
    users.push_back(User(userName));
    return &users.back();
}

User* UserContainer::addUser(const User &user){
    users.push_back(user);
    return &users.back();
}

User* UserContainer::getUserNameStartWith(const QString&starting){
    //El método solo devolverá el puntero al usuario si starting
    //concuerda sólo con un usuario.
    int matchUsers = 0;
    User* usrPtr = nullptr;
    for (unsigned int i=0; i<users.size(); i++){
        if (users.at(i).getName().startsWith(starting,Qt::CaseInsensitive)){
            matchUsers++;
            usrPtr = &users[i];
        }
    }
    if (matchUsers==1){
        return usrPtr;
    }
    else{
        return nullptr;
    }
}

int UserContainer::userExists(const QString &userName) const{
    for (unsigned int i=0; i<users.size(); i++){
        if (userName.compare(users.at(i).getName(),Qt::CaseInsensitive)==0){
            return i;
        }
    }
    return -1;
}

User* UserContainer::userAt(int index){
    return &this->users[index];
}

void UserContainer::deleteUser(const QString &userName){
    int pos = userExists(userName);
    if (pos>=0){
        users.erase(users.begin()+pos);
    }
}

unsigned int UserContainer::size() const
{
    return users.size();
}

void UserContainer::cleanUpVolatileUsersIfPossible()
{
    //Hay que ser cuidadoso al eliminar los elementos
    //de un vector cuando estás iterando a través de ellos
    //o podría crashear el programa.
    for (unsigned int i=0; i<users.size();){
        if (users[i].isRemovable()){
            users.erase(users.begin()+i);
        }
        else{
            //Sólo se incrementa cuando no se elimina
            //el usuario.
            i++;
        }
    }
}


void UserContainer::deleteUser(int index){
    if (index>=0)
    users.erase(users.begin()+index);
}
