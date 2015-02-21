#ifndef XMLMANAGER_HPP
#define XMLMANAGER_HPP

#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QFile>
#include <QTranslator>

#include "Economy/Ticket.hpp"
#include "Economy/UserAmount.hpp"

class XmlManager
{
public:
    enum{OK,FILE_NOT_OPEN,PARSE_ERROR};
    XmlManager();
    int exportToXml(QString file, Ticket *ticket);
    int loadFromXml(QString file, Ticket *ticket);
};

#endif // XMLMANAGER_HPP
