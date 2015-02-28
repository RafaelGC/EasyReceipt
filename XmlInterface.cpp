#include "XmlInterface.hpp"

XmlInterface::XmlInterface(QWidget *parent, TicketContainer *ticketContainer, Config *config)
{
    this->ticketContainer = ticketContainer;
    this->parent = parent;
    this->config = config;
}

void XmlInterface::askForTicketAndSave()
{
    if (noTicket()) return;

    QString ticketName = askForATicketName();
    if (ticketName.isNull()) return;

    Ticket *ticket = ticketContainer->getByName(ticketName);

    if (!ticket)return;

    saveTicket(ticket);
}

void XmlInterface::saveTicket(Ticket *ticket)
{
    QString path = askForSavePath(ticket);
    if (path.isNull()) return;
    config->setSavePath(path);
    if (!exportToXml(ticket,path)){
        QMessageBox::critical(parent,QObject::tr("Error"),QObject::tr("Error al guardar el archivo."));
    }
    else{
        QMessageBox::information(parent,QObject::tr("Éxito"),QObject::tr("El archivo se guardó correctamente."));
    }
}

void XmlInterface::saveAllTickets()
{
    QString path = askForSaveFolder();
    if (path.isNull()) return;

    config->setSavePath(path);

    int errorCounter = 0;
    for (Ticket *ticket : (*ticketContainer)){
        QString finalPath(path+"/"+ticket->getName()+".xml");
        if (!exportToXml(ticket,finalPath)){
            errorCounter++;
        }
    }

    if (errorCounter>0){
        QMessageBox::critical(parent,
                              QObject::tr("Error"),QString(QObject::tr("Error al guardar %1 archivo(s).")).arg(errorCounter));
    }
    else{
        QMessageBox::information(parent,QObject::tr("Éxito"),QObject::tr("Archivos guardados."));
    }

}

void XmlInterface::loadTicket(TicketLoadedListener *listener)
{

    QStringList fileNames = loadPaths();
    if (fileNames.size()>0){
        config->setSavePath(fileNames[0]);
    }

    int errorCounter = 0;

    for (QString &fileName : fileNames){
        if (fileName.isNull()) continue;
        if (!loadXml(fileName,listener)) errorCounter++;
    }

    if (errorCounter>0){
        QMessageBox::warning(parent,
                             QObject::tr("Aviso"),
                             QString(QObject::tr("Error al cargar %1 archivo. Puede estar dañado.")).arg(errorCounter));
    }
}

bool XmlInterface::noTicket()
{
    //Mensaje si no hay ticket.
    if (ticketContainer->count()==0){
        QMessageBox::warning(parent,QObject::tr("Aviso"),QObject::tr("No hay tickets que guardar."));
        return true;
    }
    return false;
}

QString XmlInterface::askForATicketName()
{
    bool ok;
    QString ticketName = QInputDialog::getItem(
                parent,
                QObject::tr("¿Qué ticket quieres guardar?"),
                QObject::tr("Selecciona el ticket que quieres guardar:"),
                ticketContainer->getTicketNamesList(),0,false,&ok);
    if (!ok){ return QString(); }
    return ticketName;
}

QString XmlInterface::askForSavePath(Ticket *ticket)
{
    return QFileDialog::getSaveFileName(
                parent,
                QObject::tr("Guardar"),
                config->getSavePath().append("/").append(ticket->getName()).append(".xml"),QObject::tr("HTML (*.xml)"));
}

QString XmlInterface::askForSaveFolder()
{
    return QFileDialog::getExistingDirectory(
                parent,
                QObject::tr("Selecciona una carpeta"),
                config->getSavePath());
}

bool XmlInterface::exportToXml(Ticket *ticket, const QString &path)
{
    XmlExporter xml(ticket);
    return xml.exportToXml(path);
}

bool XmlInterface::loadXml(const QString &fileName, TicketLoadedListener *listener)
{
    Ticket* ticket = new Ticket("");
    XmlImporter xml(fileName,ticket);
    if (xml.load()==XmlImporter::OK){
        //Validamos el nombre del ticket (el usuario podría cargar un ticket con un
        //nombre que ya esté siendo usado).
        QString validName = ticketContainer->validateName(ticket->getName());
        ticket->setName(validName);
        ticketContainer->addTicket(ticket);
        listener->ticketLoaded(ticket);
        return true;
    }
    return false;
}

QStringList XmlInterface::loadPaths()
{
    return QFileDialog::getOpenFileNames(
                    parent,
                    QObject::tr("Cargar archivo"),
                    config->getSavePath(),
                    QObject::tr("Archivos XML (*.xml)"));
}
