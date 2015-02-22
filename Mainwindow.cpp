#include "Mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Config *config, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->config = config;

    ui->setupUi(this);

    QLocale::setDefault(QLocale::system());

    usersManagerDialog = new UsersManagerDialog(&userContainer,&userDb,this);
    configDialog = new ConfigDialog(config, this);
    aboutDialog = new AboutDialog(config, this);
    updateDialog = new UpdateDialog(this);

    loadUsersFromDatabase();
    setupInterface();
    makeConnections();
    checkForUpdates();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeConnections()
{
    QObject::connect(ui->actionAbout,SIGNAL(triggered()),aboutDialog,SLOT(open()));
    QObject::connect(ui->actionExportHtml,SIGNAL(triggered()),this,SLOT(exportHtml()));
    QObject::connect(ui->actionExportAllHtml,SIGNAL(triggered()),this,SLOT(exportAllHtml()));
    QObject::connect(ui->actionUsersManager,SIGNAL(triggered()),usersManagerDialog,SLOT(open()));
    QObject::connect(ui->actionConfig,SIGNAL(triggered()),configDialog,SLOT(open()));
    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    QObject::connect(ui->actionSaveAll,SIGNAL(triggered()),this,SLOT(saveAll()));
    QObject::connect(ui->actionLoadTicket,SIGNAL(triggered()),this,SLOT(loadFile()));
    QObject::connect(ui->actionNotes,SIGNAL(triggered()),&notesWindow,SLOT(show()));

    QObject::connect(payersSelection,SIGNAL(goToManageTicket()),this,SLOT(goToManageTicket()));
    QObject::connect(createTicket,SIGNAL(goToManageTicket()),this,SLOT(goToManageTicket()));
    QObject::connect(manageTicket,SIGNAL(goToPayersSelection()),this,SLOT(goToPayersSelection()));
    QObject::connect(manageTicket,SIGNAL(goToCreateTicket()),this,SLOT(goToCreateTicket()));
    QObject::connect(payersSelection,SIGNAL(ticketHasBeenFiled()),this,SLOT(fileTicket()));
    QObject::connect(createTicket,SIGNAL(goToTotalPayout()),this,SLOT(goToTotalPayout()));
    QObject::connect(totalPayout,SIGNAL(goBack()),this,SLOT(goToCreateTicket()));

    QObject::connect(manageTicket,SIGNAL(volatileUserCreated()),payersSelection,SLOT(updatePayers()));
    QObject::connect(usersManagerDialog,SIGNAL(closedAndUsersChanged()),payersSelection,SLOT(updatePayers()));

    QObject::connect(payersSelection,SIGNAL(ticketHasBeenFiled()),this,SLOT(fileTicket()));

    QObject::connect(manageTicket,SIGNAL(cleanAllRequest()),payersSelection,SLOT(updatePayers()));
    QObject::connect(manageTicket,SIGNAL(cleanAllRequest()),payersSelection,SLOT(cleanUpRequest()));

    QObject::connect(createTicket,SIGNAL(ticketCreated()),manageTicket,SLOT(cleanAll()));

    QObject::connect(createTicket,SIGNAL(seeTicketRequest()),manageTicket,SLOT(fillUIFromTicket()));
    QObject::connect(manageTicket,SIGNAL(goToPayersSelection()),payersSelection,SLOT(fillUIFromTicket()));
    QObject::connect(createTicket,SIGNAL(saveSelectedTicketRequest(const QString&)),this,SLOT(save(const QString&)));

}

void MainWindow::setupInterface()
{
    //Configuración de la ventana.

    this->setWindowIcon(QIcon(":/icons/icon.png"));
    this->setWindowIconText("EasyReceipt");

    //Creamos las distintas páginas.

    createTicket = new CreateTicketWidget(&ticketContainer, config, ui->stackedWidget);
    ui->stackedWidget->addWidget(createTicket);

    manageTicket = new ManageTicketWidget(&userContainer, &ticketContainer, config, ui->stackedWidget);
    ui->stackedWidget->addWidget(manageTicket);

    payersSelection = new PayersSelection(&userContainer,&ticketContainer, config,ui->stackedWidget);
    ui->stackedWidget->addWidget(payersSelection);

    totalPayout = new TotalPayout(&ticketContainer,config,ui->stackedWidget);
    ui->stackedWidget->addWidget(totalPayout);

    ui->stackedWidget->setCurrentIndex(1);

    ui->actionNotes->setShortcut(QKeySequence("Ctrl+N"));
}

void MainWindow::fileTicket(){
    goToCreateTicket();
}

void MainWindow::save(const QString&ticketNameParam)
{
    Ticket *ticket = ticketContainer.getCurrentTicket();
    if (ticketNameParam.isEmpty()){
        if (ticketContainer.ticketsAmount()==0){
            QMessageBox::warning(this,tr("Aviso"),tr("No hay tickets que guardar."));
            return;
        }

        if (ui->stackedWidget->currentIndex()==1){
            //Si no estamos trabajando en ningún ticket preguntaremos cuál se quiere modificar.
            QStringList nameList;
            for (unsigned int i=0; i<ticketContainer.ticketsAmount(); i++){
                nameList<< ticketContainer.ticketAt(i)->getName();
            }
            bool ok = false;
            QString ticketName = QInputDialog::getItem(this,tr("¿Qué ticket quieres guardar?"),tr("Selecciona el ticket que quieres guardar:"),nameList,0,false,&ok);
            if (!ok) return;

            ticket = ticketContainer.getByName(ticketName);
        }
    }
    else{
        ticket = ticketContainer.getByName(ticketNameParam);
    }

    if (!ticket)return;

    QString path = QFileDialog::getSaveFileName(this,tr("Guardar"),config->getSavePath().append("/").append(ticket->getName()).append(".xml"),tr("HTML (*.xml)"));
    if (path.isNull()){ //El usuario ha cancelado la acción.
        return;
    }

    config->setSavePath(path);

    XmlExporter xml(ticket);
    if (!xml.exportToXml(path)){
        QMessageBox::critical(this,tr("Error"),tr("Error al guardar el archivo."));
    }
    else{
        QMessageBox::information(this,tr("Éxito"),tr("El archivo se guardó correctamente."));
    }
}

void MainWindow::saveAll(){
    if (ticketContainer.ticketsAmount()==0){
        QMessageBox::warning(this,tr("Aviso"),tr("No hay ningún ticket en la lista."));
        return;
    }

    if (QMessageBox::question(this,tr("¿Seguro?"),tr("Todos los archivos con el mismo nombre serán reescritos. ¿Quieres continuar?"))==QMessageBox::Yes){
        QString path = QFileDialog::getExistingDirectory(this,tr("Selecciona una carpeta"));
        if (path.isEmpty() || path.isNull()){
            return;
        }

        config->setSavePath(path);

        bool success = true;
        for (unsigned int i=0; i<ticketContainer.ticketsAmount(); i++){
            Ticket *ticket = ticketContainer.ticketAt(i);
            QString pathcpy = path;
            QString finalFile = pathcpy.append("/").append(ticket->getName()).append(".xml");
            XmlExporter xml(ticket);
            if (!xml.exportToXml(finalFile)){
                QMessageBox::critical(this,tr("Error"),QString("No se pudo guardar el archivo %1.").arg(ticket->getName()));
                success = false;
                break;
            }
        }
        if (success){
            QMessageBox::information(this,tr("Éxito"),tr("Los archivos se guardaron con éxito."));
        }

    }
}

void MainWindow::loadFile(){

    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Cargar archivo"),config->getSavePath(),tr("Archivos XML (*.xml)"));

    int errorCounter = 0;

    for (QString &fileName : fileNames){
        if (!fileName.isNull()){
            Ticket* ticket = new Ticket("");
            XmlImporter xml(fileName,ticket);
            if (xml.load()==XmlImporter::OK){
                //Validamos el nombre del ticket (el usuario podría cargar un ticket con un
                //nombre que ya esté siendo usado).
                QString validName = ticketContainer.validateName(ticket->getName());
                ticket->setName(validName);
                ticketContainer.addTicket(ticket);

                //Informamos de que se ha cargado un ticket.
                createTicket->ticketLoaded(ticket);
            }
            else{
                errorCounter++;
            }
        }
    }

    if (errorCounter>0){
        QMessageBox::warning(this,
                             tr("Aviso"),
                             QString(tr("Error al cargar %1 archivo. Puede estar dañado.")).arg(errorCounter));
    }
}

void MainWindow::goToCreateTicket(){
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::goToManageTicket(){
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::goToPayersSelection(){
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::goToTotalPayout(){
    ui->stackedWidget->setCurrentIndex(4);
}

bool MainWindow::saveHtmlFile(Ticket *ticket, QString path)
{
    HtmlManager exporter(ticket,path,config);

    return exporter.exportToHtml();

}

void MainWindow::checkForUpdates(){
    if (config->getUpdatesEnabled()){
        if (config->getLastUpdateCheck().daysTo(QDate::currentDate())>=5){
            QObject::connect(&updateManager,SIGNAL(newUpdate(Version,QString)),this,SLOT(newUpdate(Version,QString)));
            updateManager.connectToServer();
            config->setLastUpdateCheck(QDate::currentDate());
        }
    }
}


void MainWindow::exportHtml(){
    if (ticketContainer.ticketsAmount()<=0){
        QMessageBox::warning(this,tr("Aviso"),tr("No hay ningún ticket en la lista."));
        return;
    }

    Ticket * ticket = ticketContainer.getCurrentTicket();

    if (ui->stackedWidget->currentIndex()==1){
        //Si no estamos trabajando en ningún ticket preguntaremos cuál se quiere modificar.
        QStringList nameList;
        for (unsigned int i=0; i<ticketContainer.ticketsAmount(); i++){
            nameList<< ticketContainer.ticketAt(i)->getName();
        }
        bool ok = false;
        QString ticketName = QInputDialog::getItem(this,tr("¿Qué ticket quieres guardar?"),tr("Selecciona el ticket que quieres guardar:"),nameList,0,false,&ok);
        if (!ok) return;

        ticket = ticketContainer.getByName(ticketName);
    }

    if (!ticket){
        return;
    }

    //Este método guarda en formato HTML el ticket actual.

    QString path = QFileDialog::getSaveFileName(this,tr("Exportar a HTML"),config->getExportPath().append("/").append(ticket->getName()).append(".html"),tr("HTML (*.html *.htm)"));
    if (path.isNull()){ //El usuario ha cancelado la acción.
        return;
    }

    config->setExportPath(path);

    QString name = QFileInfo(path).baseName();
    if (saveHtmlFile(ticket,path)){
        QMessageBox::information(this,tr("Éxito"),tr("El archivo se guardó con éxito."));
    }
    else{
        QMessageBox::critical(this,tr("Error"),tr("El archivo no se pudo guardar."));
    }

}

void MainWindow::exportAllHtml(){
    if (ticketContainer.ticketsAmount()==0){
        QMessageBox::warning(this,tr("Aviso"),tr("No hay ningún ticket en la lista."));
        return;
    }
    if (QMessageBox::question(this,tr("¿Seguro?"),tr("Todos los archivos con el mismo nombre serán reescritos. ¿Quieres continuar?"))==QMessageBox::Yes){
        QString path = QFileDialog::getExistingDirectory(this,tr("Selecciona una carpeta"),config->getExportPath());
        if (path.isEmpty() || path.isNull()){
            return;
        }

        config->setExportPath(path);

        bool success = true;
        for (unsigned int i=0; i<ticketContainer.ticketsAmount(); i++){
            Ticket *ticket = ticketContainer.ticketAt(i);
            QString pathcpy = path;
            QString finalFile = pathcpy.append("/").append(ticket->getName()).append(".html");
            if (!saveHtmlFile(ticket,finalFile)){
                QMessageBox::critical(this,tr("Error"),QString("No se pudo guardar el archivo %1.").arg(ticket->getName()));
                success = false;
            }
        }
        if (success){
            QMessageBox::information(this,tr("Éxito"),tr("Los archivos se guardaron con éxito."));
        }

    }
}

void MainWindow::loadUsersFromDatabase()
{
    if (!userDb.connect()){
        QMessageBox::critical(this,"Error","No se pudo establecer la conexión con la base de datos local.");
        return;
    }
    int success = 0;
    QStringList userList = userDb.queryUsers(&success);
    switch (success){
    case UserDbInterface::GENERAL_ERROR:
        QMessageBox::critical(this,"Error","Error al cargar los usuarios.");
        break;
    }

    for (auto it = userList.begin(); it!=userList.end(); ++it){
        userContainer.addUser(User(*it,false));
        usersManagerDialog->addUserToList(*it);
    }

    userDb.close();
}

void MainWindow::newUpdate(Version version, QString updateUrl){
    if (config->getVersion()<version){
        updateDialog->open(version,updateUrl);
    }
}
