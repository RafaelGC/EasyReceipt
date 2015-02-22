#ifndef XMLIMPORTER_HPP
#define XMLIMPORTER_HPP

#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>

#include "Economy/Ticket.hpp"

class XmlImporter
{
private:
    QString fileName;
    Ticket *ticket;
    QDomDocument document;

    int loadFile();
    void parseXml();

    void loadTicketBasicInfo(QDomElement &element);
    void analyzeProducts(QDomElement &element);
    void analyzePayers(QDomElement &element);

public:
    enum {FILE_NOT_OPEN, PARSE_ERROR, OK};

    XmlImporter(const QString &fileName, Ticket *ticket);
    int load();
};

#endif // XMLIMPORTER_HPP
