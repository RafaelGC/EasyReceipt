#include "Mainwindow.h"
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

    payersSelection = new PayersSelection(&userContainer,ui->stackedWidget);
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

    //Por razones estéticas, si el string de los usuarios termina en ;
    //se eliminará.
    if (users.endsWith(",")){
        users = users.mid(0,users.length()-1);
    }

    //Se realizan los cálculos.
    compute(users,moneyInput);

}

void MainWindow::compute(QString users, float moneyInput, bool addToHistory){
    /*Este método recibe como parámetros un string con nombre de usuarios
     * separados por comas (se da por hecho que está bien escrito), moneyInput
     * es el precio a repartir entre dichos usuarios. Por último, el resultado
     * sólo se mostrará en la interfaz gráfica si addToHistory es true.
     * */
    //Se procede a partir el string de entrada.
    QStringList tokens = users.split(",");
    //Es necesaria una variable que contenga el número de usuarios para poder
    //calcular cuanto debe pagar cada uno.
    int usersAmount = 0;
    for (QString userName : tokens){
        if (!userName.isEmpty()){
            //Se contabiliza sólo si el string no está vacío.
            usersAmount++;
        }
    }

    //Se calcula cuanto debe pagar cada uno.
    float payOut = moneyInput/usersAmount;

    //Se vuelve a recorrer a todos los usuarios.
    for (QString userName : tokens){
        //De nuevo, si es un usuario vacío se ignora.
        if (userName.isEmpty()) continue;

        //Se trata de ver si el usuario ya existe.
        int userPos = this->userContainer.userExists(userName);
        User *currUser = nullptr;
        if (userPos>=0){
            //Si el usuario existe guardamos un puntero a él.
            currUser = this->userContainer.userAt(userPos);
        }
        else{
            //Si el usuario no existe, lo añadimos y obtenemos
            //un puntero a él.
            currUser = userContainer.addUser(userName);
        }
        //Incrementamos lo que debe pagar este usuario.
        currUser->increaseDebt(payOut);

        /*Si un usuario no debe nada y es un usuario volátil (que
        * no está guardado en la base de datos) se le eliminará.
        * Esto es de vital circunstancia por razones de comodidad.
        * Si, por error, un usuario se llama Pedro e introduzco erróneamente
        * Pedroj y elimino el registro querré eliminar también a dicho
        * usuario. Por eso hago esto. */
        if (currUser->getDebt()==0){
            if (currUser->isRemovable()){
                userContainer.deleteUser(currUser->getName());
            }
        }
    }

    //Actualizamos la interfaz.
    updateUsersPayout();

    if (addToHistory){
        //Se añade el elemento a la lista.
        addInputToHistory(users,moneyInput);
        //Limpiamos las entrada.
        usersInput->clear();
        costInput->clear();
        //Se devuelve al foco a la primera entrada,
        //por comodidad para el que escribe.
        costInput->setFocus();
    }
}


void MainWindow::addInputToHistory(QString users, float money){
    QListWidgetItem *item = new QListWidgetItem(ui->historialList);
    HistoryWidget *itemWidget = new HistoryWidget(users,QString("%1").arg(money));
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
        //Se descuenta el dinero a los usuarios implicados. NOTA: El coste está negativo porque se quiere dar marcha atrás.
        compute(hi->getNames(),-hi->getCost().toFloat(),false);

        //Por último, se elimina de la lista.
        delete ui->historialList->takeItem(ui->historialList->currentRow());
    }
}

void MainWindow::copyHistorialSelectionToInput(){
    if (ui->historialList->selectedItems().count()==1){
        HistoryWidget* hi = (HistoryWidget*)ui->historialList->itemWidget(ui->historialList->selectedItems().first());//Upcast
        costInput->setText(hi->getCost());
        usersInput->setText(hi->getNames());
        usersInput->setFocus();
    }
}

void MainWindow::updateUsersPayout(){
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

    //Esta variable contendrá el total (la suma de lo que debe pagar cada usuario).
    float totalCost = 0;
    //Ahora se estudia cada uno de los usuarios, lo que deben pagar.
    for (unsigned int j=0; j<userContainer.size(); j++){
        User* currUser = userContainer.userAt(j);
        //Sólo nos preocuparemos por él si debe algo, si no, no lo mostraremos.
        if (currUser->getDebt()>0){
            //Se actualiza el coste total.
            totalCost+=currUser->getDebt();
            QString txt = QString("%1: %2€").arg(currUser->getName()).arg(round(currUser->getDebt()*100)/100);
            QLabel *lb = new QLabel(txt);
            //Lo añadimos al vector para que se pueda eliminar en el futuro.
            usersList.push_back(lb);
            //Y lo hacemos visible.
            ui->userListLayout->addWidget(lb);
        }
    }
    //¡Se actualiza el coste total!
    ui->totalLabel->setText(QString::number(totalCost).append("€"));
}

void MainWindow::cleanAll(){
    //Debe eliminarse en orden inverso (desde el final hasta el principio)
    for (int i=ui->historialList->count(); i>0; i--){
        delete ui->historialList->takeItem(i-1);
    }
    //Se pone a 0 lo que debe cada usuario.
    for (unsigned int i=0; i<userContainer.size(); i++){
        userContainer.userAt(i)->setDebt(0);
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

    HtmlExporter exporter;

    QString path = QFileDialog::getSaveFileName(this,tr("Exportar a HTML"),QDir::currentPath(),tr("HTML (*.html *.htm)"));
    if (path.isNull()){ //El usuario ha cancelado la acción.
        return;
    }

    QString name = QFileInfo(path).baseName();

    if (ui->historialList->count()>0){
        for (int i = 0; i<ui->historialList->count(); i++){
            HistoryWidget* hi = (HistoryWidget*)ui->historialList->itemWidget(ui->historialList->item(i));
            exporter.addHistoryElement(HistoryElement(hi->getNames(),hi->getCost()));
        }

        if (exporter.save(name,path,userContainer,ui->totalLabel->text())==HtmlExporter::OK){
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
