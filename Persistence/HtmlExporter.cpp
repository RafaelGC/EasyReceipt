#include "HtmlExporter.hpp"

HtmlExporter::HtmlExporter()
{
}

void HtmlExporter::addProduct(float price, QString buyers)
{
    this->priceBuyers.push_back(std::make_pair(price,buyers));
}

void HtmlExporter::addBuyerInfo(float price, QString name)
{
    if (price!=0){
        this->individualBuyer.push_back(std::make_pair(price,name));
    }
}

void HtmlExporter::cleanHistoryElements()
{
    priceBuyers.resize(0);
}

int HtmlExporter::save(const QString &name, const QString&fullPath, float totalMoney)
{

    QFile file(fullPath);
    if (!file.open(QIODevice::WriteOnly)){
        return ERROR;
    }

    QTextStream output(&file);

    output << "<html><head><meta charset=\"UTF-8\"><title>";
    output << name;
    output << "</title></head>";
    output << "<body>";
    output << "<table border=\"2\">";
    output << "<tr><td colspan=\"2\"><h2>LISTA DE GASTOS<h2></td></tr>";
    for (unsigned int i = 0; i<priceBuyers.size(); i++){
        auto item = priceBuyers[i];
        output << "<tr><td colspan=\"1\">";
        output << item.first << "&euro;";
        output << "</td>";
        output << "<td colspan=\"1\">";
        output << item.second;
        output << "</td></tr>";
    }

    output << "<tr><td colspan=\"2\">";
    output << "<h2>GASTO INDIVIDUAL</h2>";
    output << "</td></tr>";
    for (unsigned int i = 0; i<individualBuyer.size(); i++){
        auto current = individualBuyer[i];
        output << "<tr><td>";
        output << current.second << "</td><td>" << current.first << "&euro;</td>";
        output << "</tr>";
    }
    output << "<tr><td colspan=\"2\">" << "<h2>TOTAL</h2>" << "</td></tr>";
    output << "<tr><td colspan=\"2\">" << totalMoney << "&euro;</td></tr>";

    output << "</table>";
    output << "</html>";

    file.close();

    return OK;
}
