#include "HistoryWidget.h"

HistoryWidget::HistoryWidget(const QString &names, const QString &cost, QWidget *parent) :
    QWidget(parent)
{
    this->names = new QLabel(names,this);
    this->cost = new QLabel(cost,this);

    layout = new QHBoxLayout(this);
    layout->addWidget(this->cost,1);
    layout->addWidget(this->names,4);

    this->setLayout(layout);



}

HistoryWidget::HistoryWidget(const HistoryElement &element, QWidget *parent):
    HistoryWidget(element.getNames(),element.getCost(),parent)
{

}

HistoryWidget::~HistoryWidget()
{
}

QString HistoryWidget::getNames()
{
    return this->names->text();
}

QString HistoryWidget::getCost()
{
    return this->cost->text();
}

HistoryElement HistoryWidget::getHistoryElement()
{
    return HistoryElement(this->getNames(),this->getCost());
}
