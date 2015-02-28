#include "HtmlInterface.hpp"

HtmlInterface::HtmlInterface(QWidget *parent, TicketContainer *ticketContainer, Config *config)
{
    this->parent = parent;
    this->ticketContainer = ticketContainer;
    this->config = config;
}

void HtmlInterface::saveTicket()
{
    if (noTicket()) return;

    Ticket *ticketToSave = selectTicketToSave();
    if (!ticketToSave) return;

    askForPathAndExport(ticketToSave);

}

void HtmlInterface::saveAllTickets()
{
    if (noTicket()) return;

    if (QMessageBox::question(
                parent,
                QObject::tr("¿Seguro?"),
                QObject::tr("Todos los archivos con el mismo nombre serán reescritos. ¿Quieres continuar?"))==QMessageBox::Yes){
        QString path = QFileDialog::getExistingDirectory(parent,QObject::tr("Selecciona una carpeta"),config->getExportPath());
        if (path.isNull()){
            return;
        }

        config->setExportPath(path);

        int numErrors = generateAllTickets(path);

        if (numErrors>0)
        {
            QMessageBox::warning(parent,QObject::tr("Error"),QString(QObject::tr("No se pudieron guardar %1 archivo(s).")).arg(numErrors));
        }

    }
}

void HtmlInterface::saveTicket(Ticket *ticket)
{
    askForPathAndExport(ticket);
}

bool HtmlInterface::noTicket()
{
    if (ticketContainer->count()==0){
        QMessageBox::warning(parent,QObject::tr("Aviso"),QObject::tr("No hay ningún ticket en la lista."));
        return true;
    }
    return false;
}

Ticket *HtmlInterface::selectTicketToSave()
{
    if (ticketContainer->count()==1)
    {
        return ticketContainer->ticketAt(0);
    }
    else
    {
        return askForTicket();
    }
}

Ticket *HtmlInterface::askForTicket()
{
    bool ok = false;
    QString ticketName = QInputDialog::getItem(
                parent,
                QObject::tr("¿Qué ticket quieres guardar?"),
                QObject::tr("Selecciona el ticket que quieres guardar:"),
                ticketContainer->getTicketNamesList(),0,false,&ok);
    if (!ok) return nullptr;

    return ticketContainer->getByName(ticketName);
}

void HtmlInterface::askForPathAndExport(Ticket *ticket)
{
    QString path = askForPath(ticket->getName());

    if (!exportTicket(path,ticket))
    {
        QMessageBox::warning(parent,QObject::tr("Error"),QObject::tr("El ticket no se pudo guardar."));
    }
    else
    {
        if (!path.isNull())
        {
            QMessageBox::information(parent,QObject::tr("Éxito"),QObject::tr("El ticket se guardó."));

            config->setExportPath(path);

        }
    }

}

bool HtmlInterface::exportTicket(const QString &path, Ticket *ticket)
{
    if (ticket)
    {
        if (!path.isNull())
        {
            HtmlExporter exporter(ticket,path,config);
            exporter.exportToHtml();
        }
        return true;
    }
    return false;
}

int HtmlInterface::generateAllTickets(const QString &path)
{
    int numErrors = 0;
    for (Ticket *ticket : *ticketContainer)
    {
        QString pathcpy = path;
        QString finalFile = pathcpy.append("/").append(ticket->getName()).append(".html");

        if (!exportTicket(finalFile,ticket))
        {
            numErrors++;
        }
    }
    return numErrors;
}

QString HtmlInterface::askForPath(const QString &ticketName)
{
    return QFileDialog::getSaveFileName(
                parent,
                QObject::tr("Exportar a HTML"),
                config->getExportPath().append("/").append(ticketName).append(".html"),
                QObject::tr("HTML (*.html *.htm)"));
}


