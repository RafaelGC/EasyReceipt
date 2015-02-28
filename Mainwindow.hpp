#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>

#include "Dialogs/UsersManagerDialog.hpp"
#include "Dialogs/AboutDialog.hpp"
#include "Dialogs/UpdateDialog.hpp"
#include "Dialogs/ConfigDialog.hpp"

#include "UserContainer.hpp"
#include "Config.hpp"


#include "Pages/PayersSelection.hpp"
#include "Pages/CreateTicketWidget.hpp"
#include "Pages/ManageTicketWidget.hpp"
#include "Pages/TotalPayout.hpp"

#include "Persistence/UserDbInterface.hpp"
#include "Persistence/ConfigDbInterface.hpp"
#include "Persistence/XmlImporter.hpp"
#include "Persistence/XmlExporter.hpp"

#include "Economy/Product.hpp"
#include "Economy/Ticket.hpp"
#include "Economy/TicketContainer.hpp"

#include "UserDbLoader.hpp"
#include "XmlInterface.hpp"
#include "HtmlInterface.hpp"

#include "NotesWindow.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Config *config, QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    //INTERFACES
    UserDbInterface userDb;

    //CLASES GESTORAS/CONTENEDORAS
    UpdateManager updateManager;
    TicketContainer ticketContainer;
    UserContainer userContainer;
    Config *config;

    //PÁGINAS
    ManageTicketWidget *manageTicket;
    PayersSelection *payersSelection;
    CreateTicketWidget *createTicket;
    TotalPayout *totalPayout;

    //DIÁLOGOS
    AboutDialog *aboutDialog;
    UpdateDialog *updateDialog;
    UsersManagerDialog *usersManagerDialog;
    ConfigDialog *configDialog;

    //NOTES
    NotesWindow notesWindow;

    void loadUsersFromDatabase();
    void makeConnections();
    void setupInterface();
    void checkForUpdates();

private slots:

    void exportHtml();
    void exportAllHtml();
    void fileTicket();

    void save();
    void save(const QString &ticketName);
    void saveAll();

    void loadFile();

    void newUpdate(Version version, QString updateUrl);

    //Navegación
    void goToCreateTicket();
    void goToManageTicket();
    void goToPayersSelection();
    void goToTotalPayout();

};

#endif // MAINWINDOW_H
