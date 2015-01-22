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


#include <fstream>

#include "UsersManagerDialog.hpp"
#include "UserContainer.hpp"
#include "Config.hpp"
#include "AboutDialog.hpp"
#include "UpdateDialog.hpp"

#include "CustomWidget/PayersSelection.hpp"
#include "CustomWidget/CreateTicketWidget.hpp"
#include "CustomWidget/ManageTicketWidget.hpp"
#include "CustomWidget/TotalPayout.hpp"
#include "CustomWidget/ConfigWidget.hpp"

#include "Persistence/HtmlExporter.hpp"
#include "Persistence/UserDbInterface.hpp"
#include "Persistence/ConfigDbInterface.hpp"
#include "Persistence/XmlManager.hpp"

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
    ConfigWidget *configDialog;
    UserDbInterface userDb;
    ConfigDbInterface dbConfigInterface;
    Config config;

    UpdateManager updateManager;
    TicketContainer ticketContainer;
    UserContainer userContainer;

    ManageTicketWidget *manageTicket;
    PayersSelection *payersSelection;
    CreateTicketWidget *createTicket;
    TotalPayout *totalPayout;
    AboutDialog *aboutDialog;
    UpdateDialog *updateDialog;

    void loadUsersFromDatabase();
    void makeConnections();
    void setupInterface();
    int saveHtmlFile(QString name, QString path, const Ticket *ticket);

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
