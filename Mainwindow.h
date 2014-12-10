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
#include "CustomWidget/HistoryWidget.h"
#include "Persistence/HtmlExporter.hpp"
#include "Persistence/UserDbInterface.hpp"
#include "CustomWidget/PayersSelection.hpp"

#include "delete.hpp"

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

    UserContainer userContainer;

    PayersSelection *payersSelection;

    SpaceLineEdit *costInput;
    PredictionLineEdit *usersInput;
    QPushButton *okButton, *nextButton;
    std::vector<QLabel*>usersList;

    void setupInterface();
    void makeConnections();
    void loadUsersFromDatabase();

private slots:
    void processInput();
    void compute(QString users,float cost, bool addToHistory=true);
    void deleteSelectedInput();
    void addInputToHistory(QString users, float money);
    void copyHistorialSelectionToInput();
    /*Actualiza lo que debe pagar cada usuario cada vez que se introduce
     *el coste de un nuevo producto.*/
    void updateUsersPayout();
    void saveFile();

    /*El método cleanAll() elimina las deudas de todos los usuarios
     * en la sesión actual.*/
    void cleanAll();

    void openAboutDialog();

    //Para la navegación entre paneles.
    void nextPanel();
    void previousPanel();

};

#endif // MAINWINDOW_H
