#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>

#include "Persistence/HistoryElement.hpp"

class HistoryWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel *names;
    QLabel *cost;
    QHBoxLayout *layout;
public:
    explicit HistoryWidget(const QString &names, const QString &cost, QWidget *parent = 0);
    explicit HistoryWidget(const HistoryElement&element, QWidget *parent=0);
    ~HistoryWidget();

    QString getNames();
    QString getCost();
    HistoryElement getHistoryElement();

signals:

public slots:

};

#endif // HISTORYITEM_H
