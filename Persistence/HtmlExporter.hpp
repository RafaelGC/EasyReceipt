#ifndef HTMLEXPORTER_HPP
#define HTMLEXPORTER_HPP

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "User.hpp"
#include "UserContainer.hpp"
#include "HistoryElement.hpp"

class HtmlExporter
{
private:
    QFile file;
    QTextStream stream;
    std::vector<HistoryElement> historyElements;

public:
    enum {OK,ERROR};
    HtmlExporter();

    void addHistoryElement(const HistoryElement element);
    void cleanHistoryElements();

    int save(const QString&name, const QString&fullPath,UserContainer&userContainer, const QString& totalMoney);
};

#endif // HTMLEXPORTER_HPP
