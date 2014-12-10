#include "Ticket.hpp"

Ticket::Ticket()
{
}

float Ticket::getTotalCost(){
    float total = 0;
    for (auto it=products.begin(); it!=products.end(); it++){
        total+=it->getPrice();
    }
    return total;
}

void Ticket::addProduct(Product product){

    products.push_back(product);

}

float Ticket::getCostOf(std::string name){
    float total = 0;
    for (auto it=products.begin(); it!=products.end(); it++){
        if (it->buyedBy(name)){
            total+=it->getPrice();
        }
    }
    return total;
}
