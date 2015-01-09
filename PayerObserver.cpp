#include "PayerObserver.hpp"

PayerObserver::PayerObserver(QObject*parent):QObject(parent)
{
    lineEdit = nullptr;
}

PayerObserver::PayerObserver(QString payerName, SpaceLineEdit *le):QObject(0)
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
    return QLocale::system().toFloat(lineEdit->text());
}

void PayerObserver::setAmount(float amount)
{
    lineEdit->setText(QLocale::system().toString(amount));
}


void PayerObserver::inform()
{
    float amnt = getAmount();
    emit payerChanged(payerName,amnt);
}
