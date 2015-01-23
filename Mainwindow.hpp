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
#include <QInputDialog>

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

#include "Persistence/HtmlExporter.hpp"
#include "Persistence/UserDbInterface.hpp"
#include "Persistence/ConfigDbInterface.hpp"
#include "Persistence/XmlManager.hpp"

#include "Economy/Product.hpp"
#include "Economy/Ticket.hpp"
#include "Economy/TicketContainer.hpp"

#include "NotesWindow.hpp"

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

    //INTERFACES
    UserDbInterface userDb;
    ConfigDbInterface dbConfigInterface;

    //CLASES GESTORAS/CONTENEDORAS
    UpdateManager updateManager;
    TicketContainer ticketContainer;
    UserContainer userContainer;
    Config config;

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
    NotesWindow *notesWindow;

    void loadUsersFromDatabase();
    void makeConnections();
    void setupInterface();
    int saveHtmlFile(QString name, QString path, const Ticket *ticket);
    void checkForUpdates();

private slots:

    void exportHtml();
    void exportAllHtml();
    void fileTicket();
    void save(const QString&ticketName="");
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
