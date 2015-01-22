#include "Version.hpp"

Version::Version(){
    major = 0;
    minor = 0;
}

Version::Version(int major, int minor){
    this->major = major;
    this->minor = minor;
}

Version::Version(QString version)
{
    Version tmp = fromString(version);
    this->major = tmp.getMajor();
    this->minor = tmp.getMinor();
}

Version Version::fromString(QString version){
    Version v;
    QStringList list = version.split(".");
    if (list.length()==2){
        v.setMajor(list.at(0).toInt());
        v.setMinor(list.at(1).toInt());
    }
    return v;
}

int Version::getMinor() const{
    return minor;
}

int Version::getMajor() const{
    return major;
}

void Version::setMajor(int major){
    this->major = major;
}

void Version::setMinor(int minor){
    this->minor = minor;
}

QString Version::toString() const{
    return QString("%1.%2").arg(major).arg(minor);
}

bool Version::operator==(Version &version){
    return (getMajor()==version.getMajor() && getMinor()==version.getMinor());
}

bool Version::operator>(Version &version){
    return getMajor()>version.getMajor() || (getMajor()==version.getMajor() && getMinor()>version.getMinor());
}

bool Version::operator<(Version &version){

    return getMajor()<version.getMajor() || (getMajor()==version.getMajor() && getMinor()<version.getMinor());
}

bool Version::operator>=(Version &version){
    return this->operator >(version) || this->operator ==(version);
}

bool Version::operator<=(Version &version){
    return this->operator <(version) || this->operator ==(version);
}

bool Version::operator!=(Version &version){
    return !this->operator ==(version);
}
