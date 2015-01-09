#include "Mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLocale::setDefault(QLocale::system());

    usersManagerDialog = new UsersManagerDialog(&userContainer,&userDb,this);
    configDialog = new ConfigWidget(&config, this);
    aboutDialog = new AboutDialog(this);

    loadUsersFromDatabase();
    setupInterface();
    makeConnections();


    this->setWindowIcon(QIcon(":/icons/icon.png"));
    this->setWindowIconText("Reparto");

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
}

void MainWindow::setupInterface()
{
    //Creamos las distintas páginas.

    createTicket = new CreateTicketWidget(&ticketContainer, ui->stackedWidget);
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
        QString ticketName = QInputDialog::getItem(this,tr("¿Qué ticket quieres guardar?"),tr("Selecciona el ticket que quieres guardar:"),nameList);
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
