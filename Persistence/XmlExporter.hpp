#ifndef XMLEXPORTER_HPP
#define XMLEXPORTER_HPP

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>

#include "Economy/Ticket.hpp"

class XmlExporter
{
private:
    Ticket *ticket;
    QDomDocument document;
    QDomElement mainElement;

    void createMainElement();
    void addProducts();
    void addPayers();

    bool saveFile(const QString &fileName);

public:
    XmlExporter(Ticket *ticket);

    bool exportToXml(const QString &fileName);
};

#endif // XMLEXPORTER_HPP
