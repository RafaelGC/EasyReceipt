#ifndef PAYEROBSERVER_HPP
#define PAYEROBSERVER_HPP

#include <QObject>
#include <QCheckBox>
#include <QLineEdit>

class PayerObserver : public QObject
{
    Q_OBJECT
private:
    QCheckBox *checkBox;
    QLineEdit *lineEdit;
public:
    PayerObserver(QObject*parent=0);
    PayerObserver(QCheckBox*cb,QLineEdit*le);

    QString getName();
    float getAmount();
    bool isPayer();
private slots:
    void inform();

signals:
    void payerChanged(QString payerName, bool pays, float amount);
};

#endif // PAYEROBSERVER_HPP
