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

signals:
    void goToManageTicket();
    void goToTotalPayout();
    void ticketCreated();
    void seeTicketRequest();
private slots:
    void createTicket();
    void seeSelectedTicket();
    void deleteSelectedTicket();
};

#endif // CREATETICKETWIDGET_HPP
