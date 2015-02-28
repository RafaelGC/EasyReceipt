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
}

void MainWindow::fileTicket(){
    goToCreateTicket();
}

void MainWindow::save()
{
    XmlInterface xml(this,&ticketContainer,config);
    int currIndex = ui->stackedWidget->currentIndex();
    if (currIndex==2 || currIndex==3)
    {
        xml.saveTicket(ticketContainer.getCurrentTicket());
    }
    else
    {
        xml.askForTicketAndSave();
    }
}

void MainWindow::save(const QString &ticketName)
{
    XmlInterface xml(this,&ticketContainer,config);
    xml.saveTicket(ticketContainer.getByName(ticketName));
}

void MainWindow::saveAll(){
    XmlInterface xml(this,&ticketContainer,config);
    xml.saveAllTickets();
}

void MainWindow::loadFile()
{
    XmlInterface xml(this,&ticketContainer,config);
    xml.loadTicket(createTicket);
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
    HtmlInterface htmlInterface(this,&ticketContainer,config);

    int currIndex = ui->stackedWidget->currentIndex();
    if (currIndex==2 || currIndex==3)
    {
        htmlInterface.saveTicket(ticketContainer.getCurrentTicket());
    }
    else
    {
        htmlInterface.saveTicket();
    }

}

void MainWindow::exportAllHtml(){
    HtmlInterface htmlInterface(this,&ticketContainer,config);

    htmlInterface.saveAllTickets();


}

void MainWindow::loadUsersFromDatabase()
{
    UserDbLoader userDbLoader(this,&userContainer,&userDb,usersManagerDialog);
    userDbLoader.load();
}

void MainWindow::newUpdate(Version version, QString updateUrl){
    if (config->getVersion()<version){
        updateDialog->open(version,updateUrl);
    }
}
