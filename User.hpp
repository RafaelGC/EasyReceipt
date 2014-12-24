#ifndef USER_HPP
#define USER_HPP

#include <QString>

class User
{
private:
    QString name;
    bool removable;
public:
    User();
    User(const QString &name, bool removable=true);

    void setName(QString name);

    const QString& getName() const;

    void setRemovable(bool removable);
    bool isRemovable() const;
};

#endif // USER_HPP
