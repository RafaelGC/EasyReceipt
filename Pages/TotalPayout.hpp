#ifndef TOTALPAYOUT_HPP
#define TOTALPAYOUT_HPP

#include <QWidget>

#include "ui_finalpayout.h"

#include "Economy/TicketContainer.hpp"
#include "Economy/Ticket.hpp"
#include "Economy/Debt.hpp"
#include "Economy/MultiTicketDistribution.hpp"
#include "Config.hpp"

class TotalPayout : public QWidget
{
    Q_OBJECT
private:
    Ui::FinalPayout *ui;
    TicketContainer *ticketContainer;
    Config *config;

    void showEvent(QShowEvent *);
public:
    explicit TotalPayout(TicketContainer*ticketContainer, Config *config, QWidget *parent = 0);
    ~TotalPayout();
signals:
    void goBack();
public slots:

};

#endif // TOTALPAYOUT_HPP
