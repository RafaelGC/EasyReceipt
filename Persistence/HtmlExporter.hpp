#ifndef HTMLEXPORTER_HPP
#define HTMLEXPORTER_HPP

#include <QFile>
#include <QTextStream>
#include <QString>

#include <vector>

#include "Config.hpp"

class HtmlExporter
{
private:
    QFile file;
    QTextStream stream;
    std::vector<std::pair<float,QString>>priceBuyers;
    std::vector<std::pair<float,QString>>individualBuyer;
    Config* config;
public:
    enum {OK,ERROR};
    HtmlExporter(Config *config);

    void addProduct(float price, QString buyers);
    void addBuyerInfo(float price, QString name);
    void cleanHistoryElements();

    int save(const QString&name, const QString&fullPath, float totalMoney);
};

#endif // HTMLEXPORTER_HPP
