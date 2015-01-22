#ifndef CONFIGDBINTERFACE_HPP
#define CONFIGDBINTERFACE_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDate>

#include "Config.hpp"

class ConfigDbInterface
{
private:
    QSqlDatabase db;
public:
    enum {TABLE_NOT_CREATED, OK, GENERAL_ERROR};
    static const QString DEFAULT_MONETARY_SYMBOL;

    ConfigDbInterface();

    void loadConfig(Config *config);
    void saveConfig(Config &config);

    void close();

};

#endif // CONFIGDBINTERFACE_HPP
