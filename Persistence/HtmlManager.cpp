#include "HtmlManager.hpp"


HtmlManager::HtmlManager(Ticket *ticket, QString fullPath, Config *config):
    file(fullPath), output(&file)
{
    this->ticket = ticket;
    this->config = config;
    output.setCodec("UTF-8");
}

void HtmlManager::head()
{
    output << "<html><head><meta charset=\"UTF-8\"><title>";
    output << ticket->getName();
    output << "</title>";
    output << "<STYLE type=\"text/css\">body{font-family:\"Arial\",sans-serif}.head{background-color:#CCA78E;border-bottom:solid 3px #a52a2a}h2{padding:0;margin-bottom:5px;margin-top:15px}table{border:none;border-spacing:0}td{border:none}tr:nth-child(odd){background-color:#DBC9C9}tr:nth-child(even){background-color:#DDD}</STYLE>";
    output << "</head>";
    output << "<body>";
}

void HtmlManager::startTable()
{
    output << "<table border=\"2\">";
}

void HtmlManager::listOfExpenses()
{
    output << "<tr><td class=\"head\" colspan=\"2\"><h2>" << QObject::tr("LISTA DE GASTOS") << "<h2></td></tr>";
    for (unsigned int i = 0; i<ticket->countProducts(); i++){
        output << "<tr><td colspan=\"1\">";
        output << config->constructMoney(ticket->productAt(i)->getPrice());
        output << "</td>";
        output << "<td colspan=\"1\">";
        output << ticket->productAt(i)->getStringBuyers();
        output << "</td></tr>";
    }
}

void HtmlManager::totalCost()
{
    output << "<tr><td class=\"head\" colspan=\"2\"><h2>" << QObject::tr("TOTAL") << "</h2></td></tr>";
    output << "<tr><td colspan=\"2\">" <<  config->constructMoney(ticket->getTotalCost()) << "</td></tr>";
}

void HtmlManager::individualExpenses()
{
    output << "<tr><td class=\"head\" colspan=\"2\">";
    output << "<h2>" << QObject::tr("GASTO INDIVIDUAL") <<"</h2>";
    output << "</td></tr>";

    for (QString buyer : ticket->getBuyers()){
        output << "<tr><td>";
        output << buyer << "</td><td>" <<  config->constructMoney(ticket->getPurchasePriceOf(buyer)) << "</td>";
        output << "</tr>";
    }
}

void HtmlManager::payers()
{
    if (!thereArePayers()) return;

    Payers *payers = ticket->getPayers();

    output << "<tr><td colspan=\"2\" class=\"head\"><h2>" << QObject::tr("PAGAN") << "</h2></td></tr>";
    for (unsigned int i=0; i<payers->countPayers(); i++){
        output << "<tr><td>" << (*payers)[i].getName() << "</td><td>";
        output << config->constructMoney((*payers)[i].getAmount()) << "</td></tr>";
    }
}

void HtmlManager::paymentDistribution()
{
    if (!thereArePayers()) return;

    output << "<tr><td colspan=\"2\" class=\"head\"><h2>" << QObject::tr("REPARTO") << "</h2></td></tr>";
    output << "<tr><td colspan=\"2\">";

    int message;

    PaymentDistribution distribution(ticket);

    std::vector<Debt> payoutShare = distribution.compute(&message);

    if (message==PaymentDistribution::OK)
    {
        for (unsigned int i =0; i<payoutShare.size(); i++){
            output << QString(QObject::tr("%1 debe pagar %2 a %3.<br>"))
                      .arg(payoutShare[i].getDebtor())
                      .arg(config->constructMoney(payoutShare[i].getAmount()))
                      .arg(payoutShare[i].getCreditor());
        }
    }
    else if (message==PaymentDistribution::DISTRIBUTION_IS_ALREADY_OK){
        output << QObject::tr("Reparto adecuado.");
    }
    else{
        output << QObject::tr("Sin información.");
    }
    output << "</td></tr>";
}

void HtmlManager::closeTable()
{
    output << "</table>";
}

void HtmlManager::footer()
{

    output << "</html>";
}

bool HtmlManager::thereArePayers()
{
    return ticket->getPayers()->countPayers()>0;
}

bool HtmlManager::exportToHtml()
{
    if (!file.open(QIODevice::WriteOnly)){
        return false;
    }

    head(); //Mantener fijo
    startTable(); //Mantener fijo

    //Las siguientes funciones se pueden poner en el orden que se
    //prefiera.
    listOfExpenses();
    totalCost();
    individualExpenses();
    payers();
    paymentDistribution();

    closeTable(); //Mantener fijo
    footer(); //Mantener fijo

    file.close();

    return true;

}
