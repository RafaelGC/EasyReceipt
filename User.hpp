#ifndef USER_HPP
#define USER_HPP

#include <QString>

class User
{
private:
    QString name;
    bool _volatile;
public:
    User();
    User(const QString &name, bool removable=true);

    void setName(QString name);

    const QString& getName() const;

    void setVolatile(bool removable);
    bool isVolatile() const;
};

#endif // USER_HPP
