#include "Mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ticketContainer.addTicket();

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

void MainWindow::setupInterface()
{
    costInput = new SpaceLineEdit();
    costInput->setPlaceholderText("€");
    costInput->setAlignment(Qt::AlignRight);

    QDoubleValidator *validator = new QDoubleValidator(-10000,10000,4,costInput);
    costInput->setValidator(validator);

    ui->topInputLayout->addWidget(costInput,1);

    usersInput = new PredictionLineEdit(&userContainer);
    usersInput->setPlaceholderText("Nombre1,Nombre2,Nombre3");
    ui->topInputLayout->addWidget(usersInput,3);

    okButton = new QPushButton("OK");
    ui->topInputLayout->addWidget(okButton);

    ui->stackedWidget->setCurrentIndex(0);

    payersSelection = new PayersSelection(&userContainer,&ticketContainer,ui->stackedWidget);
    ui->stackedWidget->addWidget(payersSelection);
}

void MainWindow::makeConnections()
{
    QObject::connect(usersInput,SIGNAL(returnPressed()),this,SLOT(processInput()));
    QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(processInput()));
    QObject::connect(ui->deleteSelection,SIGNAL(clicked()),this,SLOT(deleteSelectedInput()));
    QObject::connect(ui->upSelection,SIGNAL(clicked()),this,SLOT(copyHistorialSelectionToInput()));
    QObject::connect(ui->actionUsersManager,SIGNAL(triggered()),usersManagerDialog,SLOT(open()));
    QObject::connect(costInput,SIGNAL(spacePressed()),usersInput,SLOT(setFocus()));
    QObject::connect(ui->actionExportHtml,SIGNAL(triggered()),this,SLOT(saveFile()));
    QObject::connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(openAboutDialog()));
    QObject::connect(ui->clearButton,SIGNAL(clicked()),this,SLOT(cleanAll()));

    QObject::connect(ui->next,SIGNAL(clicked()),this,SLOT(nextPanel()));
    QObject::connect(payersSelection,SIGNAL(previousPanel()),this,SLOT(previousPanel()));

    QObject::connect(usersManagerDialog,SIGNAL(closedAndUsersChaned()),payersSelection,SLOT(updatePayers()));
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

void MainWindow::processInput(){
    //Nos aseguramos de que la entrada del coste no esté vacía.
    if (costInput->text().isEmpty()){
        QMessageBox::warning(this,"Error","Introduce un coste.");
        return;
    }

    //Y también de que dicho valor sea un número. En principio
    //siempre debería serlo porque Qt lo restringe.
    bool conversionOk;
    float moneyInput = costInput->text().toFloat(&conversionOk);
    if (!conversionOk){
        QMessageBox::warning(this,"Error","Formato numérico inválido.");
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

void MainWindow::compute(QString users, float cost)
{
    Product product(cost);
    QStringList tokens = users.split(",");
    for (QString userName : tokens){
        if (!userName.isEmpty()){
            if (userContainer.userExists(userName)==-1){
                //Se crea un usuario volátil.
                userContainer.addUser(userName);
                payersSelection->updatePayers();
            }

            product.addBuyer(userName);
        }
    }
    Product *productPointer = ticketContainer.getCurrentTicket()->addProduct(product);
    addInputToHistory(productPointer);

    updateUsersPayout();

    costInput->clear();
    costInput->setFocus();
    usersInput->clear();
}


void MainWindow::addInputToHistory(Product*product){
    QListWidgetItem *item = new QListWidgetItem(ui->historialList);
    HistoryWidget *itemWidget = new HistoryWidget(product);
    item->setSizeHint(itemWidget->sizeHint()); //Imprescindible.

    ui->historialList->addItem(item);
    ui->historialList->setItemWidget(item,itemWidget);

}

void MainWindow::deleteSelectedInput(){
    //Este método es el encargado de eliminar un cierto registro. Lo que tendrá
    //que hacer es tomar el elemento seleccionado, ver qué usuarios debían el dinero
    //y descontárselo.
    if (ui->historialList->selectedItems().count()==1){
        //Se obtiene el elemento seleccionado.
        HistoryWidget* hi = (HistoryWidget*)ui->historialList->itemWidget(ui->historialList->selectedItems().first());//Upcast
        ticketContainer.getCurrentTicket()->removeProduct(hi->getProduct());
        updateUsersPayout();
        delete ui->historialList->takeItem(ui->historialList->currentRow());
    }
}

void MainWindow::copyHistorialSelectionToInput(){
    if (ui->historialList->selectedItems().count()==1){
        HistoryWidget* hi = (HistoryWidget*)ui->historialList->itemWidget(ui->historialList->selectedItems().first());//Upcast
        costInput->setText(QString::number(hi->getProduct()->getPrice()));
        usersInput->setText(hi->getProduct()->getStringBuyers());
        usersInput->setFocus();
    }
}

void MainWindow::updateUsersPayout(){
    //La llamada a este método es un buen momento para eliminar
    //a los usuarios volátiles que no deban nada.
    for (unsigned int i = 0; i<userContainer.size(); i++){
        //Si lo que debe es cero y es volátil, pues se borra.
        User* usr = userContainer.userAt(i);
        if (usr->isRemovable() && ticketContainer.getCurrentTicket()->getPurchasePriceOf(usr->getName())==0){
            userContainer.deleteUser(usr->getName());
            i--; //Así solo se incrementa cuando se ha eliminado un objeto. Si no crashea.
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
    for (unsigned int i = 0; i<userContainer.size(); i++){
        /*Obtenermos el nombre del usuario.*/
        QString currName = userContainer.userAt(i)->getName();
        //Buscamos lo que el usuario debe de la factura actual.
        float money = ticketContainer.getCurrentTicket()->getPurchasePriceOf(currName,true);
        //Si no debe nada, money será 0, en ese caso no lo mostraremos.
        if (money>0){
            /*Pero si es meyor que 0 implica que ha comprado algo por lo que
             *habrá que añadir un label para que el usuario lo vea.
             * */
            QString txt = QString("%1: %2€").arg(currName).arg(money);
            QLabel *label = new QLabel(txt);
            //El objetivo de usersList es almacenar punteros a todos estos
            //labels para que puedan ser eliminados posteriormente.
            usersList.push_back(label);

            ui->userListLayout->addWidget(label);
        }
    }
    //Se actualiza el coste total de la factura.
    ui->totalLabel->setText(QString("%1€").arg(ticketContainer.getCurrentTicket()->getTotalCost(true)));

}

void MainWindow::cleanAll(){
    //Se limpia el ticket, eso quiere decir que todos los productos
    //que hay vinculados a él serán eliminados.
    ticketContainer.getCurrentTicket()->clear();

    //Debe eliminarse en orden inverso (desde el final hasta el principio)
    for (int i=ui->historialList->count(); i>0; i--){
        delete ui->historialList->takeItem(i-1);
    }
    userContainer.cleanUpVolatileUsersIfPossible();

    //Y se actualiza la interfaz gráfica para reflejar esto.
    this->updateUsersPayout();
}

void MainWindow::openAboutDialog()
{
    QMessageBox::about(this,tr("Sobre"),"Desarrollado por: Rafael González");
}

void MainWindow::nextPanel()
{
    int nPanel = ui->stackedWidget->currentIndex()+1;
    /*switch (nPanel){
        case 1:
        payersSelection->set
        break;
    }*/

    ui->stackedWidget->setCurrentIndex(nPanel);
}

void MainWindow::previousPanel()
{
    int ci = ui->stackedWidget->currentIndex()-1;
    ui->stackedWidget->setCurrentIndex(ci);
}

void MainWindow::saveFile(){
    //Este método guarda en formato HTML el ticket actual.

    HtmlExporter exporter;

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
    }

}
