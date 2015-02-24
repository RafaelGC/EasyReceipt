#ifndef HTMLINTERFACE_HPP
#define HTMLINTERFACE_HPP

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QInputDialog>

#include "Config.hpp"
#include "Economy/Ticket.hpp"
#include "Economy/TicketContainer.hpp"
#include "Persistence/HtmlExporter.hpp"

class HtmlInterface
{
private:
    QWidget *parent;
    TicketContainer *ticketContainer;
    Config *config;

    bool noTicket();
    Ticket *selectTicketToSave();
    Ticket *askForTicket();
    void askForPathAndExport(Ticket *ticket);
    QString askForPath(const QString &ticketName);
    bool exportTicket(const QString &path, Ticket *ticket);
    int generateAllTickets(const QString &path);

public:
    HtmlInterface(QWidget *parent, TicketContainer *ticketContainer, Config *config);

    void saveTicket();
    void saveTicket(Ticket *ticket);
    void saveAllTickets();
};

#endif // HTMLINTERFACE_HPP
