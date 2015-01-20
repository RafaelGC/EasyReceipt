#ifndef CREATETICKETWIDGET_HPP
#define CREATETICKETWIDGET_HPP

#include <QWidget>
#include <QDate>
#include <QListWidget>
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QMenu>

#include "ui_ticketpanel.h"
#include "Economy/TicketContainer.hpp"

class CreateTicketWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::Form *ui;
    TicketContainer* ticketContainer;
    QMenu *ticketContextMenu;

    bool eventFilter(QObject *object, QEvent *event);
public:
    explicit CreateTicketWidget(TicketContainer *ticketContainer, QWidget *parent = 0);
    ~CreateTicketWidget();
    void ticketLoaded(Ticket*ticket);

signals:
    void goToManageTicket();
    void goToTotalPayout();
    void ticketCreated();
    void seeTicketRequest();
    void saveSelectedTicketRequest(const QString&ticketName);
private slots:
    void createTicket();
    void seeSelectedTicket();
    void deleteSelectedTicket();
    void saveSelectedTicket();
};

#endif // CREATETICKETWIDGET_HPP
