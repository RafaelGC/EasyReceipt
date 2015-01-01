#ifndef CREATETICKETWIDGET_HPP
#define CREATETICKETWIDGET_HPP

#include <QWidget>
#include <QDate>
#include <QListWidget>
#include <QMessageBox>

#include "ui_ticketpanel.h"
#include "Economy/TicketContainer.hpp"

class CreateTicketWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::Form *ui;
    TicketContainer* ticketContainer;
public:
    explicit CreateTicketWidget(TicketContainer *ticketContainer, QWidget *parent = 0);
    ~CreateTicketWidget();

signals:
    void goToManageTicket();
    void goToTotalPayout();
    void ticketCreated();
    void seeTicketRequest();
public slots:
    void createTicket();
    void seeSelectedTicket();
};

#endif // CREATETICKETWIDGET_HPP
