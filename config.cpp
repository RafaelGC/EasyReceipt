#include "Config.hpp"

const QString Config::DEFAULT_MONETARY_SYMBOL = "€";


int Config::getLanguage() const
{
    return language;
}

void Config::setLanguage(int value)
{
    language = value;
}

QString Config::cleanPathIfFile(const QString &filePath)
{
    QFileInfo tmp(filePath);

    if (tmp.isFile()){
        return tmp.absoluteDir().absolutePath();
    }
    return filePath;
}

QString Config::getApplicationDataPath()
{
    QStringList sl = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    if (sl.size()>0) return sl.first().append(QDir::separator());
    else return "";
}
Config::Config()
{
    monetarySymbol = Config::DEFAULT_MONETARY_SYMBOL;
    order = SYMBOL_AFTER_AMOUNT;
}

Config::Config(const QString &monetarySymbol, int order)
{
    this->monetarySymbol  = monetarySymbol;
    this->order = order;
}

void Config::setMonetarySymbol(const QString &symbol){
    this->monetarySymbol = symbol;
}

QString Config::getMonetarySymbol(){
    return monetarySymbol;
}

void Config::setOrder(int order){
    this->order = order;
}

int Config::getOrder(){
    return order;
}

QString Config::constructMoney(float amount){
    if (order==SYMBOL_BEFORE_AMOUNT){
        return QString("%1%2").arg(getMonetarySymbol()).arg(QLocale::system().toString(amount));
    }
    else if (order==SYMBOL_AFTER_AMOUNT){
        return QString("%2%1").arg(getMonetarySymbol()).arg(QLocale::system().toString(amount));
    }
    return "";
}

void Config::setVersion(int major, int minor){
    version.setMajor(major);
    version.setMinor(minor);
}

Version Config::getVersion(){
    return this->version;
}

void Config::setLastUpdateCheck(QDate date){
    this->lastUpdateCheck = date;
}

QDate Config::getLastUpdateCheck(){
    return this->lastUpdateCheck;
}

void Config::setUpdatesEnabled(bool enabled){
    this->updatesEnabled = enabled;
}

bool Config::getUpdatesEnabled(){
    return this->updatesEnabled;
}

QString Config::getExportPath() const
{
    return exportPath;
}

void Config::setExportPath(const QString &value)
{
    exportPath = cleanPathIfFile(value);
}

QString Config::getSavePath() const
{
    return savePath;
}

void Config::setSavePath(const QString &value)
{
    savePath = cleanPathIfFile(value);
}
