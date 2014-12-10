#include "Product.hpp"

Product::Product(){
}

Product::Product(float price, std::vector<std::string> buyers){
    this->price = price;
    this->buyers = buyers;
}

Product::Product(float price){
    this->price = price;
}

bool Product::buyedBy(std::string name){
    for (auto it=buyers.begin();it!=buyers.end();it++){
        if (name==*it){
            return true;
        }
    }
    return false;
}

float Product::getPrice(){
    return price;
}

void Product::addBuyer(std::string name){
    buyers.push_back(name);
}

void Product::removeBuyer(std::string name){
    for (auto it=buyers.begin();it!=buyers.end();it++){
        if (name==*it){
            buyers.erase(it);
            break;
        }
    }
}


