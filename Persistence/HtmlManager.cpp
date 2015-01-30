#include "HtmlManager.hpp"

HtmlManager::HtmlManager(Config *config)
{
    this->config = config;
}

bool HtmlManager::exportToHtml(const Ticket *ticket, QString fullPath)
{
    QFile file(fullPath);
    if (!file.open(QIODevice::WriteOnly)){
        return false;
    }

    QTextStream output(&file);
    output.setCodec("UTF-8");

    output << "<html><head><meta charset=\"UTF-8\"><title>";
    output << ticket->getName();
    output << "</title>";
    output << "<STYLE type=\"text/css\">body{font-family:\"Arial\",sans-serif}.head{background-color:#CCA78E;border-bottom:solid 3px #a52a2a}h2{padding:0;margin-bottom:5px;margin-top:15px}table{border:none;border-spacing:0}td{border:none}tr:nth-child(odd){background-color:#DBC9C9}tr:nth-child(even){background-color:#DDD}</STYLE>";
    output << "</head>";
    output << "<body>";
    output << "<table border=\"2\">";
    output << "<tr><td class=\"head\" colspan=\"2\"><h2>" << QObject::tr("LISTA DE GASTOS") << "<h2></td></tr>";
    for (unsigned int i = 0; i<ticket->countProducts(); i++){
        output << "<tr><td colspan=\"1\">";
        output << config->constructMoney(ticket->productAt(i)->getPrice());
        output << "</td>";
        output << "<td colspan=\"1\">";
        output << ticket->productAt(i)->getStringBuyers();
        output << "</td></tr>";
    }

    output << "<tr><td class=\"head\" colspan=\"2\"><h2>" << QObject::tr("TOTAL") << "</h2></td></tr>";
    output << "<tr><td colspan=\"2\">" <<  config->constructMoney(ticket->getTotalCost()) << "</td></tr>";

    output << "<tr><td class=\"head\" colspan=\"2\">";
    output << "<h2>" << QObject::tr("GASTO INDIVIDUAL") <<"</h2>";
    output << "</td></tr>";

    for (QString buyer : ticket->getBuyers()){
        output << "<tr><td>";
        output << buyer << "</td><td>" <<  config->constructMoney(ticket->getPurchasePriceOf(buyer)) << "</td>";
        output << "</tr>";
    }

    std::vector<std::pair<QString,float>> payers = ticket->getPayers();
    if (payers.size()>0){
        output << "<tr><td colspan=\"2\" class=\"head\"><h2>" << QObject::tr("PAGAN") << "</h2></td></tr>";
        for (unsigned int i=0; i<payers.size(); i++){
            output << "<tr><td>" << payers[i].first << "</td><td>";
            output << config->constructMoney(payers[i].second) << "</td></tr>";
        }

        output << "<tr><td colspan=\"2\" class=\"head\"><h2>" << QObject::tr("REPARTO") << "</h2></td></tr>";
        output << "<tr><td colspan=\"2\">";

        int message;
        std::vector<Debt> payoutShare = ticket->computePayout(&message);
        for (unsigned int i =0; i<payoutShare.size(); i++){
            output << QString(QObject::tr("%1 debe pagar %2 a %3.<br>"))
                      .arg(payoutShare[i].getDebtor())
                      .arg(config->constructMoney(payoutShare[i].getAmount()))
                      .arg(payoutShare[i].getCreditor());
        }
        if (payoutShare.size()==0){
            output << QObject::tr("Reparto adecuado.");
        }
        output << "</td></tr>";
    }

    output << "</table>";
    output << "</html>";

    file.close();

    return true;
}
