#include "Config.hpp"

const QString Config::DEFAULT_MONETARY_SYMBOL = "€";

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
