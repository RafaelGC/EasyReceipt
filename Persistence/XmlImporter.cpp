#include "XmlImporter.hpp"

XmlImporter::XmlImporter(const QString &source, Ticket *ticket)
{
    this->fileName = source;
    this->ticket = ticket;
}

int XmlImporter::load()
{

    int state = loadFile();
    if (state!=OK){ return state; }

    parseXml();

    return OK;
}

int XmlImporter::loadFile()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return this->FILE_NOT_OPEN;
    }

    if (!document.setContent(&file)){
        file.close();
        return PARSE_ERROR;
    }
    file.close();

    return OK;
}

void XmlImporter::parseXml()
{
    //Se obtiene el elemento raíz, padre del resto de elementos: el tag 'Ticket'
    QDomElement documentElement = document.documentElement();
    loadTicketBasicInfo(documentElement);

    QDomNode node = documentElement.firstChild();
    while (!node.isNull()){
        if (node.isElement()){
            //Dentro del nodo principal encontraremos otra serie de elementos.
            QDomElement element = node.toElement();

            //Estos contienen la lista de productos, sus precios y compradores.
            if (element.tagName()=="products"){
                analyzeProducts(element);
            }
            else if (element.tagName()=="payers"){
                analyzePayers(element);
            }
        }


        node = node.nextSibling();
    }
}

void XmlImporter::loadTicketBasicInfo(QDomElement &element)
{
    QString ticketName = element.attribute("name",QObject::tr("Sin nombre"));
    //float appVersion = element.attribute("file-version","1.0").toFloat();

    ticket->setName(ticketName);
}

void XmlImporter::analyzeProducts(QDomElement &element)
{
    QDomNode productNode = element.firstChild();
    while (!productNode.isNull()){
        if (productNode.isElement()){
            QDomElement productElement = productNode.toElement();

            float price = productElement.attribute("price","0").toFloat();
            QString buyers = productElement.attribute("buyers","");
            if (!buyers.isEmpty() && price>0){
                ticket->addProduct(Product(price,buyers));
            }


        }
        productNode = productNode.nextSibling();
    }
}

void XmlImporter::analyzePayers(QDomElement &element)
{
    QDomNode payerNode = element.firstChild();
    while (!payerNode.isNull()){
        if (payerNode.isElement()){
            QDomElement payerElement = payerNode.toElement();

            float amount = payerElement.attribute("amount","0").toFloat();
            QString name = payerElement.attribute("name","");
            if (!name.isEmpty() && amount>0){
                ticket->getPayers()->setPayer(UserAmount(name,amount));
            }

        }
        payerNode = payerNode.nextSibling();
    }
}
