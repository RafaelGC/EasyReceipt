#include "XmlManager.hpp"

XmlManager::XmlManager()
{
}

int XmlManager::exportToXml(QString fileName, Ticket *ticket)
{
    QDomDocument document;

    QDomElement ticketElement = document.createElement("ticket");
    ticketElement.setAttribute("name",ticket->getName());
    ticketElement.setAttribute("appversion","1");
    document.appendChild(ticketElement);

    QDomElement products = document.createElement("products");

    for (unsigned int i=0; i<ticket->countProducts(); i++){
        const Product* product = ticket->productAt(i);
        QDomElement productElement = document.createElement("product");
        productElement.setAttribute("buyers",product->getStringBuyers());
        productElement.setAttribute("price",QString::number(product->getPrice()));
        products.appendChild(productElement);
    }
    ticketElement.appendChild(products);

    QDomElement payers = document.createElement("payers");

    for (unsigned int i = 0; i<ticket->getPayers().size(); i++){
        std::pair<QString,float> payer = ticket->getPayers()[i];
        QDomElement payerElement = document.createElement("payer");
        payerElement.setAttribute("name",payer.first);
        payerElement.setAttribute("amount",QString::number(payer.second));
        payers.appendChild(payerElement);
    }
    ticketElement.appendChild(payers);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return FILE_NOT_OPEN;
    }
    QTextStream stream(&file);

    stream << document.toString();

    file.close();

    return OK;

}

int XmlManager::loadFromXml(QString fileName, Ticket *ticket){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return this->FILE_NOT_OPEN;
    }

    QDomDocument document;
    if (!document.setContent(&file)){
        file.close();
        return PARSE_ERROR;
    }
    file.close();

    //Se obtiene el elemento raíz, padre del resto de elementos: el tag 'Ticket'
    QDomElement documentElement = document.documentElement();

    QString ticketName = documentElement.attribute("name",QObject::tr("Sin nombre"));
    //float appVersion = documentElement.attribute("appversion","1.0").toFloat();

    ticket->setName(ticketName);

    QDomNode node = documentElement.firstChild();
    while (!node.isNull()){
        if (node.isElement()){
            //Dentro del nodo principal encontraremos otra serie de elementos.
            QDomElement element = node.toElement();

            //Estos contienen la lista de productos, sus precios y compradores.
            if (element.tagName()=="products"){
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
            else if (element.tagName()=="payers"){
                QDomNode payerNode = element.firstChild();
                while (!payerNode.isNull()){
                    if (payerNode.isElement()){
                        QDomElement payerElement = payerNode.toElement();


                        float amount = payerElement.attribute("amount","0").toFloat();
                        QString name = payerElement.attribute("name","");
                        if (!name.isEmpty() && amount>0){
                            ticket->addPayer(name,amount);
                        }

                    }
                    payerNode = payerNode.nextSibling();
                }
            }
        }


        node = node.nextSibling();
    }

    return OK;
}
