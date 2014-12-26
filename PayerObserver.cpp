#include "PayerObserver.hpp"

PayerObserver::PayerObserver(QObject*parent):QObject(parent)
{
    lineEdit = nullptr;
}

PayerObserver::PayerObserver(QString payerName, QLineEdit *le):QObject(0)
{
    this->payerName = payerName;
    this->lineEdit = le;

    QObject::connect(le,SIGNAL(textEdited(QString)),this,SLOT(inform()));
}

QString PayerObserver::getName()
{
    return payerName;
}

float PayerObserver::getAmount()
{
    return lineEdit->text().toFloat();
}


void PayerObserver::inform()
{
    float amnt = lineEdit->text().toFloat();
    emit payerChanged(payerName,amnt);
}
