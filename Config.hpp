#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QString>
#include <QLocale>
#include <QDate>

#include "Version.hpp"

class Config
{
private:
    QString monetarySymbol;
    int order;
    Version version;
    QDate lastUpdateCheck;
    bool updatesEnabled;
public:
    enum {SYMBOL_BEFORE_AMOUNT,SYMBOL_AFTER_AMOUNT};
    static const QString DEFAULT_MONETARY_SYMBOL;

    Config();
    Config(const QString &monetarySymbol, int order);

    void setMonetarySymbol(const QString &symbol);
    QString getMonetarySymbol();

    void setOrder(int order);
    int getOrder();

    QString constructMoney(float amount);

    void setVersion(int major, int minor);
    Version getVersion();

    void setLastUpdateCheck(QDate date);
    QDate getLastUpdateCheck();

    void setUpdatesEnabled(bool enabled);
    bool getUpdatesEnabled();

};

#endif // CONFIG_HPP
