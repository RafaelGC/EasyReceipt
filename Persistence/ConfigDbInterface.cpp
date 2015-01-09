#include "ConfigDbInterface.hpp"

const QString ConfigDbInterface::DEFAULT_MONETARY_SYMBOL = "€";

ConfigDbInterface::ConfigDbInterface()
{
    db = QSqlDatabase::addDatabase("QSQLITE","CONFIGDB");
    db.setDatabaseName("config.db");
    if (!db.open()){
    }

    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS config(monetary_symbol VARCHAR(10), symbol_order INT)")){
        qDebug() << query.lastError().text();
    }

    if (query.exec("select COUNT(monetary_symbol) as total from config")){
        if(query.next()){
            if (query.value(0).toInt()==0){
                query.exec(QString("insert into config VALUES('%1',%2)")
                           .arg(Config::DEFAULT_MONETARY_SYMBOL).arg(Config::SYMBOL_AFTER_AMOUNT));
            }
        }
    }
}

Config ConfigDbInterface::loadConfig()
{
    QSqlQuery query(db);
    QString monetarySymbol = Config::DEFAULT_MONETARY_SYMBOL;
    int order  = Config::SYMBOL_AFTER_AMOUNT;

    if (query.exec("select * from config")){
        QSqlRecord rec = query.record();
        if (!rec.isEmpty()){
            query.next();

            int monetarySymbolCol = rec.indexOf("monetary_symbol");
            int orderCol = rec.indexOf("symbol_order");

            monetarySymbol = query.value(monetarySymbolCol).toString();
            order = query.value(orderCol).toInt();

        }
    }

    return Config(monetarySymbol,order);
}

void ConfigDbInterface::saveConfig(Config &config)
{
    QSqlQuery query(db);

    query.exec(QString("update config set monetary_symbol='%1', symbol_order='%2'")
               .arg(config.getMonetarySymbol()).arg(config.getOrder()));
}

void ConfigDbInterface::close()
{
    db.close();
}

