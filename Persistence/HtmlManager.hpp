#ifndef HTMLMANAGER_HPP
#define HTMLMANAGER_HPP

#include <QFile>
#include <QTextStream>

#include "Config.hpp"
#include "Economy/Ticket.hpp"

class HtmlManager
{
    Config *config;
public:
    HtmlManager(Config *config);

    bool exportToHtml(const Ticket *ticket, QString fullPath);
};

#endif // HTMLMANAGER_HPP
