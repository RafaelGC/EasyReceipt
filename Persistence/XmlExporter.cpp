#include "XmlExporter.hpp"

XmlExporter::XmlExporter(Ticket *ticket)
{
    this->ticket = ticket;
}

bool XmlExporter::exportToXml(const QString &fileName)
{
    createMainElement();
    addProducts();
    addPayers();

    return saveFile(fileName);
}

void XmlExporter::createMainElement()
{
    mainElement = document.createElement("ticket");
    mainElement.setAttribute("name",ticket->getName());
    mainElement.setAttribute("file-version","1");
    document.appendChild(mainElement);
}

void XmlExporter::addProducts()
{
    QDomElement products = document.createElement("products");

    for (unsigned int i=0; i<ticket->countProducts(); i++){
        const Product* product = ticket->productAt(i);
        QDomElement productElement = document.createElement("product");
        productElement.setAttribute("buyers",product->getStringBuyers());
        productElement.setAttribute("price",QString::number(product->getPrice()));
        products.appendChild(productElement);
    }
    mainElement.appendChild(products);
}

void XmlExporter::addPayers()
{
    QDomElement payers = document.createElement("payers");

    for (unsigned int i = 0; i<ticket->getPayers()->countPayers(); i++){
        UserAmount payer = (ticket->getPayers()->operator [](i));
        QDomElement payerElement = document.createElement("payer");
        payerElement.setAttribute("name",payer.getName());
        payerElement.setAttribute("amount",QString::number(payer.getAmount()));
        payers.appendChild(payerElement);
    }
    mainElement.appendChild(payers);
}

bool XmlExporter::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return false;
    }
    QTextStream stream(&file);

    stream << document.toString();

    file.close();

    return true;
}

