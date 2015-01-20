#include "ManageTicketWidget.hpp"

ManageTicketWidget::ManageTicketWidget(UserContainer *userContainer, TicketContainer *ticketContainer, Config *config, QWidget *parent) :
    QWidget(parent),ui(new Ui::TicketManagerForm)
{
    ui->setupUi(this);
    ui->historialList->installEventFilter(this);

    this->config = config;

    this->ticketContainer = ticketContainer;
    this->userContainer = userContainer;

    setupInterface();
    makeConnections();
}

ManageTicketWidget::~ManageTicketWidget()
{
    delete ui;
}

void ManageTicketWidget::setupInterface()
{
    costInput = new SpaceLineEdit();
    costInput->setPlaceholderText(config->getMonetarySymbol());
    costInput->setAlignment(Qt::AlignRight);
    costInput->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    QDoubleValidator *validator = new QDoubleValidator(-10000,10000,4,costInput);
    costInput->setValidator(validator);
    QFont font;
    font.setPixelSize(18);
    costInput->setFont(font);
    ui->topInputLayout->addWidget(costInput,1);

    usersInput = new PredictionLineEdit(userContainer);
    usersInput->setPlaceholderText("Nombre1,Nombre2,Nombre3");
    usersInput->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    usersInput->setFont(font);
    ui->topInputLayout->addWidget(usersInput,3);

    okButton = new QPushButton(QIcon(":/icons/add.png"),"");
    okButton->setIconSize(QSize(20,20));
    ui->topInputLayout->addWidget(okButton);

    productContextMenu = new QMenu(ui->historialList);
    QAction *deleteProductAction = new QAction(QIcon(":/icons/trash.png"),tr("Eliminar producto"),productContextMenu);
    productContextMenu->addAction(deleteProductAction);
    QObject::connect(deleteProductAction,SIGNAL(triggered()),this,SLOT(deleteSelectedInput()));

}

void ManageTicketWidget::makeConnections()
{
    QObject::connect(usersInput,SIGNAL(returnPressed()),this,SLOT(processInput()));
    QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(processInput()));
    QObject::connect(ui->deleteSelection,SIGNAL(clicked()),this,SLOT(deleteSelectedInput()));
    QObject::connect(ui->upSelection,SIGNAL(clicked()),this,SLOT(copyHistorialSelectionToInput()));

    QObject::connect(costInput,SIGNAL(spacePressed()),usersInput,SLOT(setFocus()));
    QObject::connect(ui->clearButton,SIGNAL(clicked()),this,SLOT(cleanAll()));

    QObject::connect(ui->next,SIGNAL(clicked()),this,SLOT(nextPressed()));
    QObject::connect(ui->cancelBtn,SIGNAL(clicked()),this,SIGNAL(goToCreateTicket()));

}

void ManageTicketWidget::showEvent(QShowEvent *){
    costInput->setFocus();
}

bool ManageTicketWidget::eventFilter(QObject *object, QEvent *event)
{
    if (event->type()==QEvent::ContextMenu){
        QContextMenuEvent *contextEvent = static_cast<QContextMenuEvent*>(event);
        QListWidgetItem *item = ui->historialList->itemAt(contextEvent->pos());
        if (item){
            productContextMenu->exec(ui->historialList->mapToGlobal(contextEvent->pos()));
        }
    }
    else if (event->type()==QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key()==Qt::Key_Delete){
            if (ui->historialList->selectedItems().count()==1){
                this->deleteSelectedInput();
            }
        }
    }

    return QObject::eventFilter(object,event);

}

void ManageTicketWidget::processInput(){
    //Nos aseguramos de que la entrada del coste no esté vacía.
    if (costInput->text().isEmpty()){
        QMessageBox::warning(this,"Error","Introduce un coste.");
        return;
    }

    //Y también de que dicho valor sea un número. En principio
    //siempre debería serlo porque Qt lo restringe.
    bool conversionOk;
    float moneyInput = QLocale::system().toFloat(costInput->text(),&conversionOk);
    if (!conversionOk){
        QMessageBox::warning(this,"Error",QString("Formato numérico inválido. Recuerta que debes usar '%1' como separador decimal.").arg(QLocale::system().decimalPoint()));
        return;
    }

    QString users = usersInput->text();
    //Igualmente, se comprueba que se haya escrito algo en los usuarios.
    if (users.isEmpty()){
        QMessageBox::warning(this,"Error","Entrada de usuarios vacía.");
        return;
    }

    //Por razones estéticas, si el string de los usuarios termina en ,
    //se eliminará.
    if (users.endsWith(",")){
        users = users.mid(0,users.length()-1);
    }

    //Se realizan los cálculos.
    compute(users,moneyInput);

}

void ManageTicketWidget::compute(QString users, float cost)
{
    Product product(cost);
    QStringList tokens = users.split(",");
    for (QString userName : tokens){
        if (!userName.isEmpty()){
            if (userContainer->userExists(userName)==-1){
                //Se crea un usuario volátil.
                userContainer->addUser(userName);
                //payersSelection->updatePayers();
                emit volatileUserCreated();
            }

            product.addBuyer(userName);
        }
    }
    Product *productPointer = ticketContainer->getCurrentTicket()->addProduct(product);
    addInputToHistory(productPointer);

    updateUsersPayout();

    costInput->clear();
    costInput->setFocus();
    usersInput->clear();
}


void ManageTicketWidget::addInputToHistory(const Product*product){
    QListWidgetItem *item = new QListWidgetItem(ui->historialList);
    HistoryWidget *itemWidget = new HistoryWidget(product);
    item->setSizeHint(itemWidget->sizeHint()); //Imprescindible.

    ui->historialList->addItem(item);
    ui->historialList->setItemWidget(item,itemWidget);

}

void ManageTicketWidget::deleteSelectedInput(){
    //Este método es el encargado de eliminar un cierto registro. Lo que tendrá
    //que hacer es tomar el elemento seleccionado, ver qué usuarios debían el dinero
    //y descontárselo.
    if (ui->historialList->selectedItems().count()==1){
        //Se obtiene el elemento seleccionado.
        HistoryWidget* hi = (HistoryWidget*)ui->historialList->itemWidget(ui->historialList->selectedItems().first());//Upcast
        ticketContainer->getCurrentTicket()->removeProduct(hi->getProduct());
        updateUsersPayout();
        delete ui->historialList->takeItem(ui->historialList->currentRow());
    }
}

void ManageTicketWidget::copyHistorialSelectionToInput(){
    if (ui->historialList->selectedItems().count()==1){
        HistoryWidget* hi = (HistoryWidget*)ui->historialList->itemWidget(ui->historialList->selectedItems().first());//Upcast
        costInput->setText(QLocale::system().toString(hi->getProduct()->getPrice()));
        usersInput->setText(hi->getProduct()->getStringBuyers());
        usersInput->setFocus();
    }
}

void ManageTicketWidget::updateUsersPayout(){
    //La llamada a este método es un buen momento para eliminar
    //a los usuarios volátiles que no deban nada.
    for (unsigned int i = 0; i<userContainer->size(); i++){
        //Si lo que debe es cero y es volátil, pues se borra.
        User* usr = userContainer->userAt(i);
        if (usr->isVolatile() && ticketContainer->getTotalSpentBy(usr->getName())==0){
            userContainer->deleteUser(usr->getName());
            i--; //Así solo se incrementa cuando se ha eliminado un objeto. Si no crashea.

            //Aunque el nombre de la señal que se va a emitir no coincide con lo que se
            //está haciendo, funcionará porque, al fin y al cabo, lo que se quiere hacer
            //es notificar que un usuario cambió para que la siguiente página se actualice.
            emit this->volatileUserCreated();
        }
    }

    //Lo más sencillo para actualizar lo que debe pagar cada usuario
    //es eliminar todos los labels que contienen lo que debían y sustituirlos
    //por unos nuevos.

    //En primer lugar se eliminan los labels que antes había. Se creó un vector
    //específicamente para guardarlos y eliminarlos en este momento.
    for (unsigned int i=0; i<usersList.size(); i++){
        delete usersList[i];
    }
    //Es importante cambiar el tamaño a 0. De lo contrario se seguirá considerando
    //que hay un cierto número de usuarios.
    usersList.resize(0);

    /*El procedimiento ahora es iterar sobre todos los usuarios y buscar lo que
     * cada uno de ellos debe pagar de la factura actual.
     * */
    for (unsigned int i = 0; i<userContainer->size(); i++){
        /*Obtenermos el nombre del usuario.*/
        QString currName = userContainer->userAt(i)->getName();
        //Buscamos lo que el usuario debe de la factura actual.
        float money = ticketContainer->getCurrentTicket()->getPurchasePriceOf(currName,true);
        //Si no debe nada, money será 0, en ese caso no lo mostraremos.
        if (money>0){
            /*Pero si es meyor que 0 implica que ha comprado algo por lo que
             *habrá que añadir un label para que el usuario lo vea.
             * */
            QString txt = QString("%1: %2").arg(currName).arg(config->constructMoney(money));
            QLabel *label = new QLabel(txt);
            //El objetivo de usersList es almacenar punteros a todos estos
            //labels para que puedan ser eliminados posteriormente.
            usersList.push_back(label);

            ui->userListLayout->addWidget(label);
        }
    }
    //Se actualiza el coste total de la factura.
    ui->totalLabel->setText(QString("%1").arg(config->constructMoney(ticketContainer->getCurrentTicket()->getTotalCost(true))));

}

void ManageTicketWidget::cleanAll(){
    //IMPORTANTE: Este método limpìa tanto la interfaz como el contenido del ticket actual.

    //Se limpia el ticket, eso quiere decir que todos los productos
    //que hay vinculados a él serán eliminados.
    ticketContainer->getCurrentTicket()->clear();

    cleanUI();
}

void ManageTicketWidget::nextPressed()
{
    if (ticketContainer->getCurrentTicket()->getTotalCost()>0){
        emit this->goToPayersSelection();
    }
    else{
        QMessageBox::warning(this,tr("Aviso"),tr("Antes de continuar, inserte algún producto."));
    }
}

void ManageTicketWidget::cleanUI()
{
    //Debe eliminarse en orden inverso (desde el final hasta el principio)
    for (int i=ui->historialList->count(); i>0; i--){
        delete ui->historialList->takeItem(i-1);
    }
    //userContainer->cleanUpVolatileUsersIfPossible();

    //Y se actualiza la interfaz gráfica para reflejar esto.
    this->updateUsersPayout();

    //Al limpiar todo, los usuarios volátiles desaparecen, es
    //recomendable hacer una limpieza en payersSelection. Se manda una
    //señal para que se haga.
    emit cleanAllRequest();

}

void ManageTicketWidget::fillUIFromTicket()
{
    this->cleanUI();

    Ticket *ticket = ticketContainer->getCurrentTicket();

    for (unsigned int i = 0; i<ticket->countProducts(); i++){
        addInputToHistory(ticket->productAt(i));
    }

    updateUsersPayout();

}
