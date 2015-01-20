#ifndef HTMLEXPORTER_HPP
#define HTMLEXPORTER_HPP

#include <QFile>
#include <QTextStream>
#include <QString>

#include <vector>
#include <tuple>

#include "Config.hpp"

class HtmlExporter
{
private:
    std::vector<std::pair<float,QString>>priceBuyers;
    std::vector<std::pair<float,QString>>individualBuyer;
    std::vector<std::pair<float,QString>>payers;
    std::vector<std::tuple<QString,float,QString>>payoutShare;
    Config* config;
public:
    enum {OK,ERROR};
    HtmlExporter(Config *config);

    void addProduct(float price, QString buyers);
    void addBuyerInfo(float price, QString name);
    void addPayer(float amount, QString name);
    void addPayoutShare(QString debtor, float amount, QString creditor);
    void cleanHistoryElements();

    int save(const QString&name, const QString&fullPath, float totalMoney);
};

#endif // HTMLEXPORTER_HPP
