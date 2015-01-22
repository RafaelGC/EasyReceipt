#include "UsersManagerDialog.hpp"

UsersManagerDialog::UsersManagerDialog(UserContainer* userContainer, UserDbInterface *userDb, QWidget *parent):QDialog(parent),
    ui(new Ui::UsersManager)
{
    this->userContainer = userContainer;
    this->userDb = userDb;

    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QObject::connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(addUser()));
    QObject::connect(ui->userName,SIGNAL(returnPressed()),this,SLOT(addUser()));
    QObject::connect(ui->deleteBtn,SIGNAL(clicked()),this,SLOT(deleteUser()));
    QObject::connect(this,SIGNAL(rejected()),this,SLOT(dialogClosed()));

    updated = false;
}

UsersManagerDialog::~UsersManagerDialog(){
    delete ui;
}

void UsersManagerDialog::addUser(){
    if (!ui->userName->text().isEmpty()){
        if (userContainer->userExists(ui->userName->text())==-1){
            updated = true;
            userContainer->addUser(ui->userName->text()); //Se añade al contenedor.
            if (!userDb->saveUser(ui->userName->text())){ //Se guarda en la base de datos.
                QMessageBox::warning(this,tr("Error"),tr("No se pudo guardar el perfil en la base de datos."));
            }

            ui->usersList->addItem(ui->userName->text());
            ui->userName->clear();
        }
        else{
            QMessageBox::warning(this,"Error","El nombre ya está añadido.");
        }
    }
    else{
        QMessageBox::warning(this,"Error","Nombre vacío.");
    }
}

void UsersManagerDialog::deleteUser(){
    if (ui->usersList->selectedItems().count()==1){
        QListWidgetItem *item = ui->usersList->takeItem(ui->usersList->currentRow());
        if (item){
            userContainer->deleteUser(item->text());
            if (!userDb->deleteUser(item->text())){ //Se guarda en la base de datos.
                QMessageBox::warning(this,tr("Error"),tr("No se pudo eliminar el perfil de la base de datos."));
            }
            else{
                updated = true;
            }
            delete item;
        }
    }
}

void UsersManagerDialog::open(){
    QDialog::open();
}

void UsersManagerDialog::addUserToList(const QString &name){
    //Añade un usuario a la lista (AL WIDGET), pero no al contenedor.
    ui->usersList->addItem(name);
}

void UsersManagerDialog::dialogClosed(){
    if (updated){
        emit this->closedAndUsersChaned();
    }
    updated = false;
}
