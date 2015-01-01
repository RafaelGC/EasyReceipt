#include "Mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    usersManagerDialog = new UsersManagerDialog(&userContainer,&userDb,this);

    loadUsersFromDatabase();
    setupInterface();
    makeConnections();


    this->setWindowIcon(QIcon(":/icons/icon.png"));
    this->setWindowIconText("ZCalc");

}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::makeConnections()
{
    QObject::connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(openAboutDialog()));
    QObject::connect(ui->actionExportHtml,SIGNAL(triggered()),this,SLOT(saveFile()));
    QObject::connect(ui->actionUsersManager,SIGNAL(triggered()),usersManagerDialog,SLOT(open()));

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

    manageTicket = new ManageTicketWidget(&userContainer, &ticketContainer, ui->stackedWidget);
    ui->stackedWidget->addWidget(manageTicket);

    payersSelection = new PayersSelection(&userContainer,&ticketContainer,ui->stackedWidget);
    ui->stackedWidget->addWidget(payersSelection);

    totalPayout = new TotalPayout(&ticketContainer,ui->stackedWidget);
    ui->stackedWidget->addWidget(totalPayout);

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::openAboutDialog(){
    QMessageBox::about(this,tr("Sobre"),"Desarrollado por: Rafael González");
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

void MainWindow::saveFile(){
    //Este método guarda en formato HTML el ticket actual.

    /*HtmlExporter exporter;

    QString path = QFileDialog::getSaveFileName(this,tr("Exportar a HTML"),QDir::currentPath(),tr("HTML (*.html *.htm)"));
    if (path.isNull()){ //El usuario ha cancelado la acción.
        return;
    }

    QString name = QFileInfo(path).baseName();

    if (ui->historialList->count()>0){
        for (unsigned int i=0; i<ticketContainer.getCurrentTicket()->countProducts(); i++){
            const Product *pr = ticketContainer.getCurrentTicket()->productAt(i);
            exporter.addProduct(pr->getPrice(),pr->getStringBuyers());
        }

        for (unsigned int i=0; i<userContainer.size(); i++){
            QString name = userContainer.userAt(i)->getName();
            exporter.addBuyerInfo(ticketContainer.getCurrentTicket()->getPurchasePriceOf(name,true),name);
        }

        if (exporter.save(name,path,ticketContainer.getCurrentTicket()->getTotalCost(true))==HtmlExporter::OK){
            QMessageBox::information(this,tr("Éxito"),tr("El archivo se guardó con éxito."));
        }
        else{
            QMessageBox::warning(this,tr("Error"),tr("No se pudo guardar el archivo."));
        }
    }
    else{
        QMessageBox::warning(this,tr("Aviso"),tr("No hay nada que guardar."));
    }*/

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
