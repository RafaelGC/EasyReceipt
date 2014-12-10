#include "UserDbInterface.hpp"

UserDbInterface::UserDbInterface()
{
}

UserDbInterface::~UserDbInterface()
{

}

bool UserDbInterface::connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE","USERSDB");
    db.setDatabaseName("profiles.db");
    if (!db.open()){
        return false;
    }

    return true;

}

void UserDbInterface::close()
{

}

QStringList UserDbInterface::queryUsers(int *ok)
{
    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS users(name VARCHAR(35) PRIMARY KEY)")){
        if (ok){
            *ok = UserDbInterface::TABLE_NO_CREATED;
            return QStringList();
        }
    }

    if (query.exec("select * from users")){
        QSqlRecord rec = query.record();
        if (!rec.isEmpty()){
            int nameCol = rec.indexOf("name");
            QStringList strlst;
            while (query.next()){
                QString tmpName = query.value(nameCol).toString();
                strlst.append(tmpName);
            }
            if (ok){
                *ok = OK;
            }
            return strlst;
        }
        else{
            if (ok){
                *ok = GENERAL_ERROR;
                return QStringList();
            }
        }
    }
    else{
        if (ok){
            *ok = UserDbInterface::GENERAL_ERROR;
            return QStringList();
        }
    }

    return QStringList();
}

bool UserDbInterface::saveUser(const QString &userName)
{
    QSqlQuery query(db);
    if (query.exec(QString("insert into users VALUES('%1')").arg(userName))){
        return true;
    }
    return false;
}

bool UserDbInterface::deleteUser(const QString &userName){
    QSqlQuery query(db);
    if (query.exec(QString("delete from users where name='%1'").arg(userName))){
        return true;
    }
    return false;
}
