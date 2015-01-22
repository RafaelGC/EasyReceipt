#include "CreateTicketWidget.hpp"

CreateTicketWidget::CreateTicketWidget(TicketContainer*ticketContainer, Config *config, QWidget *parent) :
    QWidget(parent),ui(new Ui::Form){
    ui->setupUi(this);
    ui->ticketList->installEventFilter(this);

    this->config = config;
    this->ticketContainer = ticketContainer;

    ui->ticketName->setText(QDate::currentDate().toString("yyyy-MM-dd"));

    ticketContextMenu = new QMenu(ui->ticketList);
    QAction *seeTicketAction = new QAction(QIcon(":/icons/pencil.png"),tr("Ver ticket"),ticketContextMenu);
    QAction *deleteTicketAction = new QAction(QIcon(":/icons/trash.png"),tr("Eliminar ticket"),ticketContextMenu);
    QAction *saveTicketAction = new QAction(QIcon(":/icons/floppy.png"),tr("Guardar ticket"),ticketContextMenu);

    ticketContextMenu->addAction(seeTicketAction);
    ticketContextMenu->addAction(deleteTicketAction);
    ticketContextMenu->addAction(saveTicketAction);
    QObject::connect(seeTicketAction,SIGNAL(triggered()),this,SLOT(seeSelectedTicket()));
    QObject::connect(deleteTicketAction,SIGNAL(triggered()),this,SLOT(deleteSelectedTicket()));
    QObject::connect(saveTicketAction,SIGNAL(triggered()),this,SLOT(saveSelectedTicket()));

    QObject::connect(ui->addTicketBtn,SIGNAL(clicked()),this,SLOT(createTicket()));
    QObject::connect(ui->ticketName,SIGNAL(returnPressed()),this,SLOT(createTicket()));
    QObject::connect(ui->seeTicketBtn,SIGNAL(clicked()),this,SLOT(seeSelectedTicket()));
    QObject::connect(ui->deleteTicketBtn,SIGNAL(clicked()),this,SLOT(deleteSelectedTicket()));
    QObject::connect(ui->totalPayoutBtn,SIGNAL(clicked()),this,SIGNAL(goToTotalPayout()));

    QObject::connect(ui->ticketList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(seeSelectedTicket()));
}

CreateTicketWidget::~CreateTicketWidget(){
    delete ui;
}

void CreateTicketWidget::ticketLoaded(Ticket *ticket){
    QListWidgetItem *item = new QListWidgetItem(QIcon(":/icons/ticket.png"),ticket->getName());
    ui->ticketList->addItem(item);
    ui->ticketList->setIconSize(QSize(30,32));
}

void CreateTicketWidget::createTicket(){
    if (ui->ticketName->text().isEmpty()){
        QMessageBox::warning(this,tr("Aviso"),tr("Debes darle un nombre al ticket."));
        return;
    }

    Ticket *createdTicket = ticketContainer->addTicket(ui->ticketName->text(),true);

    if (createdTicket==nullptr){
        QMessageBox::warning(this,tr("Aviso"),tr("Ya existe un ticket con ese nombre."));
    }
    else{
        QListWidgetItem *item = new QListWidgetItem(QIcon(":/icons/ticket.png"),ui->ticketName->text());
        ui->ticketList->addItem(item);
        ui->ticketList->setIconSize(QSize(30,32));

        emit this->ticketCreated();
        //emit this->goToManageTicket(); Si se descomenta esto se mandará al usuario a la edición del ticket cuando lo cree.
    }
}

bool CreateTicketWidget::eventFilter(QObject *object, QEvent *event)
{
    if (event->type()==QEvent::ContextMenu){
        QContextMenuEvent *contextEvent = static_cast<QContextMenuEvent*>(event);
        QListWidgetItem *item = ui->ticketList->itemAt(contextEvent->pos());
        if (item){
            ticketContextMenu->exec(ui->ticketList->mapToGlobal(contextEvent->pos()));
        }
    }
    else if (event->type()==QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key()==Qt::Key_Delete){
            this->deleteSelectedTicket();
        }
    }

    return QObject::eventFilter(object,event);
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

void CreateTicketWidget::saveSelectedTicket(){
    emit this->saveSelectedTicketRequest(ui->ticketList->currentItem()->text());
}


