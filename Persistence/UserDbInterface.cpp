#include "UserDbInterface.hpp"

UserDbInterface::UserDbInterface()
{
    db = QSqlDatabase::addDatabase("QSQLITE","USERSDB");
    db.setDatabaseName("profiles.db");
}

UserDbInterface::~UserDbInterface()
{

}

bool UserDbInterface::connect()
{
    if (!db.open()){
        return false;
    }

    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS users(name VARCHAR(35) PRIMARY KEY)")){
        //
    }

    return true;

}

void UserDbInterface::close()
{
    db.close();
}

QStringList UserDbInterface::queryUsers(bool *ok)
{
    QSqlQuery query(db);

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
                *ok = true;
            }
            return strlst;
        }
        else{
            if (ok){
                *ok = false;
                return QStringList();
            }
        }
    }
    else{
        if (ok){
            *ok = false;
        }
        return QStringList();
    }

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
