#ifndef VERSION_HPP
#define VERSION_HPP

#include <QString>
#include <QDebug>

class Version
{
private:
    int minor;
    int major;
public:
    static Version fromString(QString version);
    Version();
    Version(int major, int minor);
    Version(QString version);

    int getMinor() const;
    int getMajor() const;
    void setMajor(int major);
    void setMinor(int minor);
    QString toString() const;
    bool operator==(Version&version);
    bool operator>(Version&version);
    bool operator<(Version&version);
    bool operator>=(Version&version);
    bool operator<=(Version&version);
    bool operator!=(Version&version);
};

#endif // VERSION_HPP
