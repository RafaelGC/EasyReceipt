#ifndef CREATETICKETWIDGET_HPP
#define CREATETICKETWIDGET_HPP

#include <QWidget>
#include <QDate>
#include <QListWidget>
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
#include <time.h>

#include "ui_ticketpanel.h"
#include "Economy/TicketContainer.hpp"

#include "Config.hpp"
#include "UpdateManager.hpp"
#include "TicketLoadedListener.hpp"

class CreateTicketWidget : public QWidget, public TicketLoadedListener
{
    Q_OBJECT
private:
    Ui::Form *ui;
    TicketContainer* ticketContainer;
    QMenu *ticketContextMenu;
    Config *config;


    bool eventFilter(QObject *object, QEvent *event);
public:
    explicit CreateTicketWidget(TicketContainer *ticketContainer, Config *config, QWidget *parent = 0);
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
