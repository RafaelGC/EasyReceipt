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
    const Product*product;//Puntero al producto que representa.
public:
    explicit HistoryWidget(const Product *product, QWidget *parent = 0);
    ~HistoryWidget();
    const Product *getProduct();

signals:

public slots:

};

#endif // HISTORYITEM_H
