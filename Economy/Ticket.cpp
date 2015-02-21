#include "Ticket.hpp"

Ticket::Ticket(QString ticketName)
{
    this->ticketName = ticketName;
}

Ticket::~Ticket()
{
    clear();
}

void Ticket::setName(const QString &name){
    this->ticketName = name;
}

QString Ticket::getName() const
{
    return this->ticketName;
}

float Ticket::getTotalCost(bool rounded) const{
    float total = 0;
    for (auto it=products.begin(); it!=products.end(); it++){
        total+=(*it)->getPrice();
    }

    if (rounded){
        total = round(total*100)/100;
    }

    return total;
}

Product* Ticket::addProduct(Product product){
    //Se devuelve un puntero al producto añadido para dar algo
    //de control al usuario sobre el producto.
    Product *pr = new Product(product);

    products.push_back(pr);

    return pr;

}

void Ticket::removeProduct(const Product *product){
    for (auto it = products.begin(); it!=products.end(); it++){
        if ((*it)==product){
            delete (*it);
            products.erase(it);
            break;
        }
    }
}

float Ticket::getPurchasePriceOf(QString name, bool rounded) const{
    float total = 0;
    for (auto it=products.begin(); it!=products.end(); it++){
        if ((*it)->buyedBy(name)){
            total+=(*it)->getPayout();
        }
    }

    if (rounded){
        total = round(total*100)/100;
    }

    return total;
}

void Ticket::clear(){
    for (unsigned int i = 0; i<products.size(); i++){
        delete products[i];
    }
    products.clear();
}

const Product *Ticket::productAt(int index) const{
return products[index];
}

unsigned int Ticket::countProducts() const{
    return products.size();
}

Payers* Ticket::getPayers(){
    return &payers;
}

QStringList Ticket::getBuyers() const
{
    QStringList list;

    //Estudiamos cada producto.
    for (unsigned int i=0; i<products.size(); i++){
        //Obtenemos los compradores de cada producto.
        QStringList currentList = products[i]->getBuyers();
        //Los estudiamos individualmente.
        for (QString user : currentList){
            //Y, en el caso de que no estén ya en nuestra lista de retorno,
            //los añadimos.
            if (!list.contains(user)){
                list.append(user);
            }
        }
    }

    return list;
}



