#ifndef MANAGETICKETWIDGET_HPP
#define MANAGETICKETWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

#include "ui_products.h"

#include "CustomWidget/SpaceLineEdit.hpp"
#include "CustomWidget/PredictionLineEdit.hpp"
#include "CustomWidget/HistoryWidget.hpp"

#include "UserContainer.hpp"
#include "Economy/TicketContainer.hpp"

class ManageTicketWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::TicketManagerForm *ui;

    UserContainer *userContainer;
    TicketContainer *ticketContainer;

    SpaceLineEdit *costInput;
    PredictionLineEdit *usersInput;
    QPushButton *okButton, *nextButton;
    std::vector<QLabel*>usersList;

    void setupInterface();
    void makeConnections();

public:
    explicit ManageTicketWidget(UserContainer *userContainer, TicketContainer *ticketContainer, QWidget *parent=0);
    ~ManageTicketWidget();

private slots:
    void processInput();
    void compute(QString users,float cost);
    void deleteSelectedInput();//
    void addInputToHistory(const Product*product);
    void copyHistorialSelectionToInput();
    /*Actualiza lo que debe pagar cada usuario cada vez que se introduce
     *el coste de un nuevo producto.*/
    void updateUsersPayout(); //
    /*El método cleanAll() elimina las deudas de todos los usuarios
     * en la sesión actual.*/
    void cleanAll();

    void nextPressed();
public slots:
    void cleanUI();
    void fillUIFromTicket();
signals:
    void volatileUserCreated();
    void cleanAllRequest();
    //Para la navegación entre paneles.
    void goToPayersSelection();
    void goToCreateTicket();

};

#endif // MANAGETICKETWIDGET_HPP
