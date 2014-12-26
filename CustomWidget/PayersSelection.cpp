#include "PayersSelection.hpp"

PayersSelection::PayersSelection(UserContainer *userContainer, TicketContainer *ticketContainer, QWidget *parent) :
    QWidget(parent),ui(new Ui::PlayersSelectorForm)
{
    ui->setupUi(this);
    this->ticketContainer = ticketContainer;
    this->userContainer = userContainer;

    payersLayout = new QGridLayout(ui->payersGroupBox);
    updatePayers();

    payoutLayout = new QVBoxLayout(ui->payoutGroupBox);
    ui->payoutGroupBox->setLayout(payoutLayout);

    QObject::connect(ui->backBtn,SIGNAL(clicked()),this,SIGNAL(previousPanel()));
    QObject::connect(ui->calcBtn,SIGNAL(clicked()),this,SLOT(compute()));

}

PayersSelection::~PayersSelection()
{
    clearPayerObservers();
    delete ui;
}

void PayersSelection::payerChanged(QString payerName, float amount)
{
    //Cada vez que se realiza un cambio se debe reajustar el reparto.
    /*for (unsigned int i = 0; i<payerObservers.size(); i++){
    }*/
}

void PayersSelection::updatePayers(){
    /*Primero se eliminan toda la lista de usuarios para
     * que pueda ser generada de nuevo. */
    QLayoutItem *child;
    while ((child = payersLayout->takeAt(0)) != 0) {
        if (child->widget()){
            child->widget()->setParent(nullptr);
        }
        delete child;
    }
    clearPayerObservers();

    /*Y ahora se genera la nueva lista.*/
    unsigned int i = 0;
    for (; i<userContainer->size(); i++){
        /*Se crean dos instancias de los elementos widgets necesarios.*/
        //QCheckBox *ck = new QCheckBox(userContainer->userAt(i)->getName());
        QLineEdit *td = new QLineEdit();
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

void PayersSelection::compute(){
    QLayoutItem *child;
    while ((child = payoutLayout->takeAt(0)) != nullptr) {
        if (child->widget()){
            child->widget()->setParent(nullptr);
            delete child->widget();
        }
        delete child;
    }

    std::vector<std::pair<QString,float>>positiveUser;
    std::vector<std::pair<QString,float>>negativeUser;

    float total = 0;
    for (unsigned int i=0; i<payerObservers.size(); i++){
        //Guardamos lo que ha gastado.
        float userSpent = ticketContainer->getCurrentTicket()->getPurchasePriceOf(payerObservers[i]->getName());
        //Guardamos lo que ha pagado.
        float userPay = payerObservers[i]->getAmount();

        total+=userPay;

        //Calculamos la diferencia.
        float neto = userSpent-userPay;
        if (neto>0){
            //Si es positivo significa que el usuario ha pagado de menos.
            positiveUser.push_back(std::make_pair(payerObservers[i]->getName(),neto));
        }
        else if (neto<0){
            //Si es negativo significa que ha pagado de más.
            negativeUser.push_back(std::make_pair(payerObservers[i]->getName(),-neto));
        }
        //(Si fuera 0 significa que el usuario ha pagado lo justo y está en paz con todos.)

        //qDebug() << (ticketContainer->getCurrentTicket()->getPurchasePriceOf(payerObservers[i]->getName())-payerObservers[i]->getAmount());
    }

    if (total!=ticketContainer->getCurrentTicket()->getTotalCost()){
        QMessageBox::warning(this,tr("Aviso"),tr("El total pagado no coincide con el de la lista."));
        return;
    }

    for (unsigned int i=0; i<negativeUser.size(); i++){
        //Paso 1: buscamos un usuario con un saldo negativo.

        float nUser = negativeUser[i].second;
        QString nUserName = negativeUser[i].first;

        //Paso 2: buscamos un usuario con saldo positivo que le de el dinero.
        for (unsigned int j=0; j<positiveUser.size(); j++){
            //Nos preguntamos, ¿este usuario puede pagar completamente al otro?
            float pUser = positiveUser[j].second;

            //Si el usuario ya no tiene ningún beneficio, significa que ya ha pagado
            //todo lo que podía. Se pasa al siguiente.
            if (pUser==0){
                continue;
            }

            QString pUserName = positiveUser[j].first;

            float incr = std::min(pUser,nUser);

            payoutLayout->addWidget(new QLabel(QString("%1 debe pagar %2%3 a %4").arg(pUserName)
                                               .arg(round(incr*100)/100).arg("€").arg(nUserName)));

            //qDebug() << pUserName << " tiene un beneficio de " << pUser << " así que pagará "
                     //<< incr << " a " << nUserName << " para equilibrar.";

            nUser-=incr;
            pUser-=incr;

            positiveUser[j].second = pUser;
            negativeUser[i].second = nUser;

            if (nUser==0){
                //Si la deuda del usuario negativo ya ha sido pagada, pasamos al
                //siguiente usuario negativo.
                break;
            }

        }
    }

}

void PayersSelection::clearPayerObservers()
{
    for (unsigned int i=0; i<payerObservers.size(); i++){
        delete payerObservers[i];
    }
    payerObservers.clear();
}
