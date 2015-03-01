#include "ConfigDbInterface.hpp"

const QString ConfigDbInterface::DEFAULT_MONETARY_SYMBOL = "€";

ConfigDbInterface::ConfigDbInterface(){
    db = QSqlDatabase::addDatabase("QSQLITE","CONFIGDB");
    db.setDatabaseName(Config::getApplicationDataPath().append("config.db"));
}

void ConfigDbInterface::loadConfig(Config *config)
{
    QSqlQuery query(db);
    QString monetarySymbol = Config::DEFAULT_MONETARY_SYMBOL;
    int order  = Config::SYMBOL_AFTER_AMOUNT;
    QDate lastUpdateCheck = QDate::currentDate();
    bool updatesEnabled = true;
    QString savePath;
    QString exportPath;
    int language = QLocale::system().language();

    if (query.exec("select * from config limit 1")){
        QSqlRecord rec = query.record();
        if (!rec.isEmpty()){
            query.next();

            int monetarySymbolCol = rec.indexOf("monetary_symbol");
            int orderCol = rec.indexOf("symbol_order");
            int lastUpdateCheckCol = rec.indexOf("last_update_check");
            int updatesEnabledCol = rec.indexOf("updates_enabled");
            int savePathCol = rec.indexOf("save_path");
            int exportPathCol = rec.indexOf("export_path");
            int languageCol = rec.indexOf("language");

            monetarySymbol = query.value(monetarySymbolCol).toString();
            order = query.value(orderCol).toInt();
            lastUpdateCheck = QDate::fromString(query.value(lastUpdateCheckCol).toString(),"yyyy-MM-dd");
            updatesEnabled = query.value(updatesEnabledCol).toBool();
            savePath = query.value(savePathCol).toString();
            exportPath = query.value(exportPathCol).toString();
            language = query.value(languageCol).toInt();
        }
    }

    config->setMonetarySymbol(monetarySymbol);
    config->setOrder(order);
    config->setLastUpdateCheck(lastUpdateCheck);
    config->setUpdatesEnabled(updatesEnabled);
    config->setSavePath(savePath);
    config->setExportPath(exportPath);
    config->setLanguage(language);
}

void ConfigDbInterface::saveConfig(Config &config){
    QSqlQuery query(db);

    query.exec(QString("update config set monetary_symbol='%1', symbol_order='%2', "
                       "last_update_check='%3', updates_enabled=%4, "
                       "save_path='%5', export_path='%6', language=%7")
               .arg(config.getMonetarySymbol()).arg(config.getOrder())
               .arg(config.getLastUpdateCheck().toString("yyyy-MM-dd"))
               .arg(config.getUpdatesEnabled())
               .arg(config.getSavePath())
               .arg(config.getExportPath())
               .arg(config.getLanguage()));
}

bool ConfigDbInterface::connect(){
    if (!db.open()){
        return false;
    }

    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS "
                    "config(monetary_symbol VARCHAR(10), symbol_order INTEGER, "
                    "last_update_check TEXT, updates_enabled INTEGER, "
                    "save_path TEXT, export_path TEXT, "
                    "language INTEGER)")){
        qDebug() << query.lastError().text();
    }

    //La primera vez es necesario introducir unos valores por defecto.
    if (query.exec("select COUNT(monetary_symbol) as total from config")){
        if (query.next()){
            if (query.value(0).toInt()==0){
                query.exec(QString("insert into config VALUES('%1',%2,'%3','1','%4','%5',%6)")
                           .arg(Config::DEFAULT_MONETARY_SYMBOL).arg(Config::SYMBOL_AFTER_AMOUNT)
                           .arg(QDate::currentDate().toString("yyyy-MM-dd"))
                           .arg(QDir::homePath())
                           .arg(QDir::homePath())
                           .arg(QLocale::system().language()));
            }
        }
    }
    return true;
}

void ConfigDbInterface::close(){
    db.close();
}

