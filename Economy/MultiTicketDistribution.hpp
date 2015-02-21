#ifndef MULTITICKETDISTRIBUTION_HPP
#define MULTITICKETDISTRIBUTION_HPP

#include "Economy/Debt.hpp"
#include "Economy/PaymentDistribution.hpp"
#include "Economy/TicketContainer.hpp"
#include "Economy/Ticket.hpp"

#include <QDebug>

class MultiTicketDistribution
{
private:
    TicketContainer *ticketContainer;

    std::vector<Debt> definitiveList;

public:
    MultiTicketDistribution(TicketContainer *ticketContainer);
    std::vector<Debt> compute();

    void analyzeTicket(Ticket *ticket);
    void analyzeDebt(Debt &debt);
    Debt *lookForSameDebtInContainer(const Debt &debt);
};

#endif // MULTITICKETDISTRIBUTION_HPP
