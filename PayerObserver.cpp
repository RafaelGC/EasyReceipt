#include "PayerObserver.hpp"

PayerObserver::PayerObserver(QObject*parent):QObject(parent)
{
    checkBox = nullptr;
    lineEdit = nullptr;
}

PayerObserver::PayerObserver(QCheckBox *cb, QLineEdit *le):QObject(0)
{
    this->checkBox = cb;
    this->lineEdit = le;

    QObject::connect(cb,SIGNAL(toggled(bool)),this,SLOT(inform()));
    QObject::connect(le,SIGNAL(textEdited(QString)),this,SLOT(inform()));
}

QString PayerObserver::getName()
{
    return checkBox->text();
}

float PayerObserver::getAmount()
{
    return lineEdit->text().toFloat();
}

bool PayerObserver::isPayer()
{
    return checkBox->isChecked();
}

void PayerObserver::inform()
{
    float amnt = lineEdit->text().toFloat();
    emit payerChanged(checkBox->text(),checkBox->isChecked(),amnt);
}
