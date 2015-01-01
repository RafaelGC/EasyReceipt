#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QToolBar>
#include <QFileDialog>
#include <QFileInfo>
#include <QCheckBox>
#include <QGridLayout>
#include <QPointer>

#include <fstream>

#include "UsersManagerDialog.hpp"
#include "UserContainer.hpp"

#include "CustomWidget/PredictionLineEdit.hpp"
#include "CustomWidget/SpaceLineEdit.hpp"
#include "CustomWidget/HistoryWidget.hpp"
#include "CustomWidget/PayersSelection.hpp"
#include "CustomWidget/CreateTicketWidget.hpp"
#include "CustomWidget/ManageTicketWidget.hpp"
#include "CustomWidget/TotalPayout.hpp"

#include "Persistence/HtmlExporter.hpp"
#include "Persistence/UserDbInterface.hpp"

#include "Economy/Product.hpp"
#include "Economy/Ticket.hpp"
#include "Economy/TicketContainer.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    UsersManagerDialog *usersManagerDialog;
    QSqlDatabase db;
    UserDbInterface userDb;

    TicketContainer ticketContainer;
    UserContainer userContainer;

    ManageTicketWidget *manageTicket;
    PayersSelection *payersSelection;
    CreateTicketWidget *createTicket;
    TotalPayout *totalPayout;

    void loadUsersFromDatabase();
    void makeConnections();
    void setupInterface();

private slots:

    void saveFile();
    void openAboutDialog();
    void fileTicket();

    //Navegación
    void goToCreateTicket();
    void goToManageTicket();
    void goToPayersSelection();
    void goToTotalPayout();

};

#endif // MAINWINDOW_H
