#include "Product.hpp"

Product::Product(){
}

Product::Product(float price, std::vector<QString> buyers){
    this->price = price;
    this->buyers = buyers;
}

Product::Product(float price){
    this->price = price;
}

bool Product::buyedBy(QString name) const{
    for (auto it=buyers.begin();it!=buyers.end();it++){
        if (name==*it){
            return true;
        }
    }
    return false;
}

float Product::getPrice() const{
    return price;
}

void Product::addBuyer(QString name){
    buyers.push_back(name);
}

void Product::removeBuyer(QString name){
    for (auto it=buyers.begin();it!=buyers.end();it++){
        if (name==*it){
            buyers.erase(it);
            break;
        }
    }
}

float Product::getPayout() const{
    return price/buyers.size();
}

QString Product::getStringBuyers() const{
    QString result;
    for (unsigned int i = 0; i<buyers.size(); i++){
        result.append(buyers.at(i));
        if (i!=buyers.size()-1){
            result.append(",");
        }
    }
    return result;
}


