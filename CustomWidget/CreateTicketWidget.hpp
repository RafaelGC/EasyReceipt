#ifndef CREATETICKETWIDGET_HPP
#define CREATETICKETWIDGET_HPP

#include <QWidget>
#include "ui_ticketpanel.h"

class CreateTicketWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::Form *ui;
public:
    explicit CreateTicketWidget(QWidget *parent = 0);
    ~CreateTicketWidget();

signals:

public slots:

};

#endif // CREATETICKETWIDGET_HPP
