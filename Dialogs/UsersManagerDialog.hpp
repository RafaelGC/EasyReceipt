#ifndef USERSMANAGERDIALOG_HPP
#define USERSMANAGERDIALOG_HPP

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>

#include "ui_UsersManager.h"
#include "UserContainer.hpp"
#include "Persistence/UserDbInterface.hpp"

class UsersManagerDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::UsersManager *ui;
    UserContainer *userContainer;
    UserDbInterface *userDb;

    bool updated;
public:
    UsersManagerDialog(UserContainer *userContainer, UserDbInterface*userDb, QWidget *parent=0);
    ~UsersManagerDialog();
    void addUserToList(const QString &name);
public slots:
    void open();

private slots:
    void addUser();
    void deleteUser();
    void dialogClosed();
signals:
    //Esta señal es emitida cuando se cierra el diálogo y los usuarios han
    //cambiado: se ha añadido o eliminado alguno por lo que será necesario
    //notificarlo.
    void closedAndUsersChaned();
};

#endif // USERSMANAGERDIALOG_HPP
