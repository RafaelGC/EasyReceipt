#ifndef PAYERSSELECTION_HPP
#define PAYERSSELECTION_HPP

#include <QMessageBox>
#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QLayoutItem>

#include <algorithm>

#include "Economy/Ticket.hpp"
#include "Economy/TicketContainer.hpp"
#include "Economy/Debt.hpp"
#include "PayerObserver.hpp"
#include "UserContainer.hpp"
#include "ui_payersselector.h"

class PayersSelection : public QWidget
{
    Q_OBJECT
private:
    Ui::PlayersSelectorForm *ui;
    TicketContainer*ticketContainer;
    UserContainer*userContainer;
    QGridLayout *payersLayout;
    QVBoxLayout *payoutLayout;

    std::vector<PayerObserver*> payerObservers;

    void clearPayerObservers();

    void showEvent(QShowEvent *);
public:
    explicit PayersSelection(UserContainer *userContainer,TicketContainer*ticketContainer,QWidget *parent = 0);
    ~PayersSelection();
private slots:
    void payerChanged(QString payerName, float amount);
    void fileTicket();
public slots:
    void updatePayers();
    void clearPayout();

signals:
    void nextPanel();
    void previousPanel();
    void ticketHasBeenFiled();

};

#endif // PAYERSSELECTION_HPP
