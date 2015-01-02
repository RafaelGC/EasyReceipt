#include "CreateTicketWidget.hpp"

CreateTicketWidget::CreateTicketWidget(TicketContainer*ticketContainer, QWidget *parent) :
    QWidget(parent),ui(new Ui::Form){
    ui->setupUi(this);

    this->ticketContainer = ticketContainer;

    ui->ticketName->setText(QDate::currentDate().toString("yyyy-MM-dd"));

    QObject::connect(ui->addTicketBtn,SIGNAL(clicked()),this,SLOT(createTicket()));
    QObject::connect(ui->ticketName,SIGNAL(returnPressed()),this,SLOT(createTicket()));
    QObject::connect(ui->seeTicketBtn,SIGNAL(clicked()),this,SLOT(seeSelectedTicket()));
    QObject::connect(ui->deleteTicketBtn,SIGNAL(clicked()),this,SLOT(deleteSelectedTicket()));
    QObject::connect(ui->totalPayoutBtn,SIGNAL(clicked()),this,SIGNAL(goToTotalPayout()));

    QObject::connect(ui->ticketList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(seeSelectedTicket()));
}

CreateTicketWidget::~CreateTicketWidget()
{
    delete ui;
}

void CreateTicketWidget::createTicket()
{
    Ticket *createdTicket = ticketContainer->addTicket(ui->ticketName->text(),true);

    if (createdTicket==nullptr){
        QMessageBox::warning(this,tr("Aviso"),tr("Ya existe un ticket con ese nombre."));
    }
    else{
        ui->ticketList->addItem(ui->ticketName->text());
        emit this->ticketCreated();
        emit this->goToManageTicket();
    }
}

void CreateTicketWidget::seeSelectedTicket(){
    if (ui->ticketList->selectedItems().count()==1){
        QString ticketName = ui->ticketList->currentItem()->text();
        Ticket*ticket = ticketContainer->getByName(ticketName);
        if (ticket==nullptr) return;

        ticketContainer->setCurrentTicket(ticket);

        emit this->seeTicketRequest();
        emit this->goToManageTicket();
    }

}

void CreateTicketWidget::deleteSelectedTicket(){
    if (ui->ticketList->selectedItems().count()==1){
        if (QMessageBox::question(this,tr("¿Seguro?"),tr("¿Quieres eliminar el ticket?"))==QMessageBox::Yes){
            ticketContainer->deleteTicket(ui->ticketList->currentItem()->text());
            delete ui->ticketList->takeItem(ui->ticketList->currentRow());
        }
    }
}
