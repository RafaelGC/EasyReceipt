#include "Ticket.hpp"

Ticket::Ticket()
{
}

Ticket::~Ticket()
{
    clear();
}

float Ticket::getTotalCost() const{
    float total = 0;
    for (auto it=products.begin(); it!=products.end(); it++){
        total+=(*it)->getPrice();
    }
    return total;
}

Product* Ticket::addProduct(float price, std::vector<QString> buyers)
{
    return addProduct(Product(price,buyers));
}

Product* Ticket::addProduct(Product product){
    //Se devuelve un puntero al producto añadido para dar algo
    //de control al usuario sobre el producto.
    Product *pr = new Product(product);

    products.push_back(pr);

    return pr;

}

void Ticket::removeProduct(Product *product){
    for (auto it = products.begin(); it!=products.end(); it++){
        if ((*it)==product){
            delete (*it);
            products.erase(it);
            break;
        }
    }
}

float Ticket::getPurchasePriceOf(QString name) const{
    float total = 0;
    for (auto it=products.begin(); it!=products.end(); it++){
        if ((*it)->buyedBy(name)){
            total+=(*it)->getPayout();
        }
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
