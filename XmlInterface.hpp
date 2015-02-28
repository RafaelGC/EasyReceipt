#ifndef XMLINTERFACE_HPP
#define XMLINTERFACE_HPP

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

#include "Economy/TicketContainer.hpp"
#include "Economy/Ticket.hpp"
#include "Persistence/XmlExporter.hpp"
#include "Persistence/XmlImporter.hpp"
#include "Config.hpp"
#include "TicketLoadedListener.hpp"

class XmlInterface
{
private:
    TicketContainer *ticketContainer;
    QWidget *parent;
    Config *config;

    bool noTicket();
    QString askForATicketName();
    QString askForSavePath(Ticket *ticket);
    QString askForSaveFolder();
    bool exportToXml(Ticket *ticket, const QString &path);

    bool loadXml(const QString &fileName, TicketLoadedListener *listener);
    QStringList loadPaths();
public:
    XmlInterface(QWidget *parent, TicketContainer *ticketContainer, Config *config);

    void askForTicketAndSave();
    void saveTicket(Ticket *ticket);
    void saveAllTickets();

    void loadTicket(TicketLoadedListener *listener);
};

#endif // XMLINTERFACE_HPP
