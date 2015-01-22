#include "Mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    dbConfigInterface.loadConfig(&config);
    config.setVersion(1,0); //Versión 1.0. Se establece desde código.

    ui->setupUi(this);

    QLocale::setDefault(QLocale::system());

    usersManagerDialog = new UsersManagerDialog(&userContainer,&userDb,this);
    configDialog = new ConfigWidget(&config, this);
    aboutDialog = new AboutDialog(&config, this);
    updateDialog = new UpdateDialog(this);

    loadUsersFromDatabase();
    setupInterface();
    makeConnections();


    this->setWindowIcon(QIcon(":/icons/icon.png"));
    this->setWindowIconText("EasyReceipt");

    if (config.getUpdatesEnabled()){
        if (config.getLastUpdateCheck().daysTo(QDate::currentDate())>=5){
            QObject::connect(&updateManager,SIGNAL(newUpdate(Version,QString)),this,SLOT(newUpdate(Version,QString)));
            updateManager.connectToServer();
            config.setLastUpdateCheck(QDate::currentDate());
        }
    }

}

MainWindow::~MainWindow()
{
    dbConfigInterface.saveConfig(config);
    dbConfigInterface.close();
    userDb.close();
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

    QObject::connect(payersSelection,SIGNAL(goToManageTicket()),this,SLOT(goToManageTicket()));
    QObject::connect(createTicket,SIGNAL(goToManageTicket()),this,SLOT(goToManageTicket()));
    QObject::connect(manageTicket,SIGNAL(goToPayersSelection()),this,SLOT(goToPayersSelection()));
    QObject::connect(manageTicket,SIGNAL(goToCreateTicket()),this,SLOT(goToCreateTicket()));
    QObject::connect(payersSelection,SIGNAL(ticketHasBeenFiled()),this,SLOT(fileTicket()));
    QObject::connect(createTicket,SIGNAL(goToTotalPayout()),this,SLOT(goToTotalPayout()));
    QObject::connect(totalPayout,SIGNAL(goBack()),this,SLOT(goToCreateTicket()));

    QObject::connect(manageTicket,SIGNAL(volatileUserCreated()),payersSelection,SLOT(updatePayers()));
    QObject::connect(usersManagerDialog,SIGNAL(closedAndUsersChaned()),payersSelection,SLOT(updatePayers()));

    QObject::connect(payersSelection,SIGNAL(ticketHasBeenFiled()),this,SLOT(fileTicket()));

    QObject::connect(manageTicket,SIGNAL(cleanAllRequest()),payersSelection,SLOT(updatePayers()));
    QObject::connect(manageTicket,SIGNAL(cleanAllRequest()),payersSelection,SLOT(clearPayout()));

    QObject::connect(createTicket,SIGNAL(ticketCreated()),manageTicket,SLOT(cleanAll()));

    QObject::connect(createTicket,SIGNAL(seeTicketRequest()),manageTicket,SLOT(fillUIFromTicket()));
    QObject::connect(createTicket,SIGNAL(seeTicketRequest()),payersSelection,SLOT(fillUIFromTicket()));
    QObject::connect(createTicket,SIGNAL(saveSelectedTicketRequest(const QString&)),this,SLOT(save(const QString&)));
}

void MainWindow::setupInterface()
{
    //Creamos las distintas páginas.

    createTicket = new CreateTicketWidget(&ticketContainer, &config, ui->stackedWidget);
    ui->stackedWidget->addWidget(createTicket);

    manageTicket = new ManageTicketWidget(&userContainer, &ticketContainer, &config, ui->stackedWidget);
    ui->stackedWidget->addWidget(manageTicket);

    payersSelection = new PayersSelection(&userContainer,&ticketContainer, &config,ui->stackedWidget);
    ui->stackedWidget->addWidget(payersSelection);

    totalPayout = new TotalPayout(&ticketContainer,&config,ui->stackedWidget);
    ui->stackedWidget->addWidget(totalPayout);

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::fileTicket(){
    goToCreateTicket();
}

void MainWindow::save(const QString&ticketNameParam)
{
    XmlManager xml;
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

    QString path = QFileDialog::getSaveFileName(this,tr("Guardar"),QDir::currentPath().append("/").append(ticket->getName()).append(".xml"),tr("HTML (*.xml)"));
    if (path.isNull()){ //El usuario ha cancelado la acción.
        return;
    }

    if (xml.exportToXml(path,ticket)==XmlManager::FILE_NOT_OPEN){
        QMessageBox::critical(this,tr("Error"),tr("Error al guardar el archivo."));
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
        bool success = true;
        for (unsigned int i=0; i<ticketContainer.ticketsAmount(); i++){
            Ticket *ticket = ticketContainer.ticketAt(i);
            QString pathcpy = path;
            QString finalFile = pathcpy.append("/").append(ticket->getName()).append(".xml");
            XmlManager xml;
            if (xml.exportToXml(finalFile,ticket)==XmlManager::FILE_NOT_OPEN){
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
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Cargar archivo"),QDir::currentPath(),
                                                    tr("Archivos XML (*.xml)"));
    if (!fileName.isNull()){
        XmlManager xml;
        Ticket* ticket = ticketContainer.addTicket("-",false);
        if (xml.loadFromXml(fileName,ticket)==XmlManager::OK){
            createTicket->ticketLoaded(ticket);
        }
        else{
            QMessageBox::warning(this,tr("Aviso"),tr("Error al cargar el archivo. Puede estar dañado."));
        }
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

int MainWindow::saveHtmlFile(QString name, QString path, const Ticket *ticket)
{
    HtmlExporter exporter(&config);
    for (unsigned int i=0; i<ticket->countProducts(); i++){
        const Product *pr = ticket->productAt(i);
        exporter.addProduct(round(pr->getPrice()*100)/100,pr->getStringBuyers());
    }

    QStringList buyers = ticket->getBuyers();
    for (QString buyer : buyers){
        exporter.addBuyerInfo(ticket->getPurchasePriceOf(buyer,true),buyer);
    }

    int message = 0;
    std::vector<Debt> debts = ticket->computePayout(&message);
    if (message==Ticket::SUCCESS){
        std::vector<std::pair<QString,float>> payers = ticket->getPayers();
        for (auto current : payers){
            exporter.addPayer(current.second,current.first);
        }
        for (Debt current : debts){
            exporter.addPayoutShare(current.getDebtor(),current.getAmount(true),current.getCreditor());
        }
    }

    return exporter.save(name,path,ticket->getTotalCost(true));

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

    QString path = QFileDialog::getSaveFileName(this,tr("Exportar a HTML"),QDir::currentPath().append("/").append(ticket->getName()).append(".html"),tr("HTML (*.html *.htm)"));
    if (path.isNull()){ //El usuario ha cancelado la acción.
        return;
    }

    QString name = QFileInfo(path).baseName();
    if (saveHtmlFile(name,path,ticket)==HtmlExporter::OK){
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
        QString path = QFileDialog::getExistingDirectory(this,tr("Selecciona una carpeta"));
        if (path.isEmpty() || path.isNull()){
            return;
        }
        bool success = true;
        for (unsigned int i=0; i<ticketContainer.ticketsAmount(); i++){
            Ticket *ticket = ticketContainer.ticketAt(i);
            QString pathcpy = path;
            QString finalFile = pathcpy.append("/").append(ticket->getName()).append(".html");
            if (saveHtmlFile(ticket->getName(),finalFile,ticket)==HtmlExporter::ERROR){
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

    case UserDbInterface::TABLE_NO_CREATED:
        QMessageBox::critical(this,"Error","No se pudo crear la tabla de la base de datos.");
        break;
    }

    for (auto it = userList.begin(); it!=userList.end(); ++it){
        userContainer.addUser(User(*it,false));
        usersManagerDialog->addUserToList(*it);
    }
}

void MainWindow::newUpdate(Version version, QString updateUrl){
    if (config.getVersion()<version){
        updateDialog->open(version,updateUrl);
    }
}
