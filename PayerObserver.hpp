#ifndef PAYEROBSERVER_HPP
#define PAYEROBSERVER_HPP

#include <QObject>
#include <QCheckBox>
#include <QLocale>

#include "CustomWidget/SpaceLineEdit.hpp"

class PayerObserver : public QObject
{
    Q_OBJECT
private:
    SpaceLineEdit *lineEdit;
    QString payerName;
public:
    PayerObserver(QObject*parent=0);
    PayerObserver(QString payerName, SpaceLineEdit*le);

    QString getName();
    float getAmount();
    void setAmount(float amount);
private slots:
    void inform();

signals:
    void payerChanged(QString payerName, float amount);
};

#endif // PAYEROBSERVER_HPP
