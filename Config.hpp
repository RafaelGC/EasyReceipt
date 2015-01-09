#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QString>
#include <QLocale>

class Config
{
private:
    QString monetarySymbol;
    int order;

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

};

#endif // CONFIG_HPP
