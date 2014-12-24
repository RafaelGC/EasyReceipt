#include "HistoryWidget.hpp"

HistoryWidget::HistoryWidget(Product *product, QWidget *parent) :
    QWidget(parent){

    this->product = product;

    this->names = new QLabel(product->getStringBuyers(),this);
    this->cost = new QLabel(QString("%1").arg(product->getPrice()),this);

    layout = new QHBoxLayout(this);
    layout->addWidget(this->cost,1);
    layout->addWidget(this->names,4);

    this->setLayout(layout);


}

HistoryWidget::~HistoryWidget(){
}

Product *HistoryWidget::getProduct()
{
    return product;
}
