#include "PayersSelection.hpp"

PayersSelection::PayersSelection(UserContainer *userContainer, TicketContainer *ticketContainer, Config *config, QWidget *parent) :
    QWidget(parent),ui(new Ui::PlayersSelectorForm)
{
    ui->setupUi(this);
    this->config = config;
    this->ticketContainer = ticketContainer;
    this->userContainer = userContainer;

    payersLayout = new QGridLayout(ui->payersGroupBox);
    updatePayers();

    payoutLayout = new QVBoxLayout(ui->payoutGroupBox);
    ui->payoutGroupBox->setLayout(payoutLayout);

    QObject::connect(ui->backBtn,SIGNAL(clicked()),this,SIGNAL(goToManageTicket()));
    QObject::connect(ui->fileBtn,SIGNAL(clicked()),this,SLOT(fileTicket()));

}

PayersSelection::~PayersSelection()
{
    clearPayerObservers();
    delete ui;
}

void PayersSelection::payerChanged(QString name, float amount)
{
    ticketContainer->getCurrentTicket()->getPayers()->setPayer(UserAmount(name,amount));

    updateUsersPayout();

}

void PayersSelection::fileTicket()
{
    emit ticketHasBeenFiled();
}

void PayersSelection::updatePayers(){
    /*Primero se eliminan toda la lista de usuarios para
     * que pueda ser gerada de nuevo. */
    clearLayout(payersLayout);
    clearPayerObservers();

    /*Y ahora se genera la nueva lista.*/
    unsigned int i = 0;
    for (; i<userContainer->size(); i++){
        /*Se crean dos instancias de los elementos widgets necesarios.*/
        //QCheckBox *ck = new QCheckBox(userContainer->userAt(i)->getName());
        SpaceLineEdit *td = new SpaceLineEdit();
        /*Se añade un validador para que sólo se puedan introducir números.*/
        td->setValidator(new QDoubleValidator(0,100000,3,td));
        td->setPlaceholderText(tr("Cantidad que pagó"));

        /*Se añaden al layout.*/
        //payersLayout->addWidget(ck,i,0,1,1,Qt::AlignLeft);
        payersLayout->addWidget(new QLabel(userContainer->userAt(i)->getName()),i,0,1,1);
        payersLayout->addWidget(td,i,1,1,1,Qt::AlignLeft);

        /*Ahora los dos elementos se almacenan en un objeto que contendrá
         * referencias a ellos y que estará pendiente de informarnos cuando
         * estos elementos se hayan sometido a alguna modificación. */

        PayerObserver *po = new PayerObserver(userContainer->userAt(i)->getName(),td);

        payerObservers.push_back(po);
        QObject::connect(po,SIGNAL(payerChanged(QString,float))
                         ,this,SLOT(payerChanged(QString,float)));
    }
    payersLayout->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding),++i,0);
    payersLayout->setColumnStretch(1,1);
}

void PayersSelection::clearPayerObservers()
{
    for (unsigned int i=0; i<payerObservers.size(); i++){
        delete payerObservers[i];
    }
    payerObservers.clear();
}

void PayersSelection::clearLayout(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()){
            child->widget()->setParent(nullptr);
            delete child->widget();
        }
        delete child;
    }
}

void PayersSelection::fillUIFromTicket()
{
    Ticket *ticket = ticketContainer->getCurrentTicket();

    updatePayers();
    updateUsersPayout();

    for (unsigned int i=0; i<payerObservers.size(); i++){
        float amount = ticket->getPayers()->payedBy(payerObservers[i]->getName());
        if (amount>0){
            payerObservers[i]->setAmount(amount);
        }
    }

}

void PayersSelection::updateUsersPayout()
{
    clearLayout(payoutLayout);

    int outputMessage;

    PaymentDistribution distribution(ticketContainer->getCurrentTicket());
    std::vector<Debt> debtList = distribution.compute(&outputMessage);

    if (outputMessage==PaymentDistribution::OK){
        //Interpretar salida.
        for (unsigned int i=0; i<debtList.size(); i++){
            payoutLayout->addWidget(new QLabel(QString(tr("%1 debe pagar %2 a %3")).arg(debtList[i].getDebtor())
                                               .arg(config->constructMoney(debtList[i].getAmount(true))).arg(debtList[i].getCreditor())));
        }
    }
    else if (outputMessage==PaymentDistribution::DISTRIBUTION_IS_ALREADY_OK){
        payoutLayout->addWidget(new QLabel(tr("<b>Reparto adecuado.</b>")));
    }
    else{
        payoutLayout->addWidget(
                    new QLabel(QString(tr("<b>El dinero pagado no coincide con el coste de la compra.</b>"
                                       "<br>Recuerda que el separador decimal en tu sistema es '%1'."))
                               .arg(QLocale::system().decimalPoint())));
    }

    /*int message = -1;
    std::vector<Debt> debts = ticketContainer->getCurrentTicket()->computePayout(&message);
    if (message==Ticket::MONEY_DOES_NOT_MATCH){
        payoutLayout->addWidget(
                    new QLabel(QString(tr("<b>El dinero pagado no coincide con el coste de la compra.</b>"
                                       "<br>Recuerda que el separador decimal en tu sistema es '%1'."))
                               .arg(QLocale::system().decimalPoint())));
    }
    else if (message==Ticket::SUCCESS && debts.size()==0){
        payoutLayout->addWidget(new QLabel(tr("<b>Reparto adecuado.</b>")));
    }
    else{
        for (unsigned int i=0; i<debts.size(); i++){
            payoutLayout->addWidget(new QLabel(QString(tr("%1 debe pagar %2 a %3")).arg(debts[i].getDebtor())
                                               .arg(config->constructMoney(debts[i].getAmount(true))).arg(debts[i].getCreditor())));
        }
    }*/
}

void PayersSelection::cleanUpRequest()
{
    this->clearLayout(payoutLayout);
}

void PayersSelection::showEvent(QShowEvent *)
{
    ui->totalPrice->setText(config->constructMoney(ticketContainer->getCurrentTicket()->getTotalCost()));
}
