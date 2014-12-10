#ifndef USER_HPP
#define USER_HPP

#include <QString>

class User
{
private:
    QString name;
    float debt;
    bool removable;
public:
    User();
    User(const QString &name, bool removable=true);

    void setName(QString name);
    void setDebt(float debt);
    void increaseDebt(float increment);

    float getDebt() const;
    const QString& getName() const;

    void setRemovable(bool removable);
    bool isRemovable() const;
};

#endif // USER_HPP
