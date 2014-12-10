#include "HtmlExporter.hpp"

HtmlExporter::HtmlExporter()
{
}

void HtmlExporter::addHistoryElement(const HistoryElement element)
{
    this->historyElements.push_back(element);
}

void HtmlExporter::cleanHistoryElements()
{
    historyElements.clear();
}

int HtmlExporter::save(const QString &name, const QString&fullPath, UserContainer &userContainer, const QString &totalMoney)
{

    /*QString fileName = name;
    if (fileName.isEmpty()){
        fileName = "unnamed";
    }
    QString fileNameExt = fileName.append(".html");*/

    QFile file(fullPath);
    if (!file.open(QIODevice::WriteOnly)){
        return ERROR;
    }

    QTextStream output(&file);

    output << "<html><head><title>";
    output << name;
    output << "</title></head>";
    output << "<body>";
    output << "<table border=\"2\">";
    output << "<tr><td colspan=\"2\"><h2>LISTA DE GASTOS<h2></td></tr>";
    for (unsigned int i = 0; i<historyElements.size(); i++){
        HistoryElement he = historyElements[i];
        output << "<tr><td colspan=\"1\">";
        output << he.getCost();
        output << "</td>";
        output << "<td colspan=\"1\">";
        output << he.getNames();
        output << "</td></tr>";
    }

    output << "<tr><td colspan=\"2\">";
    output << "<h2>GASTO INDIVIDUAL</h2>";
    output << "</td></tr>";
    for (unsigned int i = 0; i<userContainer.size(); i++){
        User *usr = userContainer.userAt(i);
        if (usr->getDebt()!=0){
            output << "<tr><td>";
            output << usr->getName() << "</td><td>" << usr->getDebt() << "</td>";
            output << "</tr>";
        }
    }
    output << "<tr><td colspan=\"2\">" << "<h2>TOTAL</h2>" << "</td></tr>";
    output << "<tr><td colspan=\"2\">" << totalMoney << "</td></tr>";

    output << "</table>";
    output << "</html>";

    file.close();

    return OK;
}
