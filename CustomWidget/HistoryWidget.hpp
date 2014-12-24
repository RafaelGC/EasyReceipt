#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>

#include "Economy/Product.hpp"


class HistoryWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel *names, *cost;
    QHBoxLayout *layout;
    Product*product;//Puntero al producto que representa.
public:
    explicit HistoryWidget(Product *product, QWidget *parent = 0);
    ~HistoryWidget();
    Product *getProduct();

signals:

public slots:

};

#endif // HISTORYITEM_H
