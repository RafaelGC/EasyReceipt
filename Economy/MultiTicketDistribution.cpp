#include "MultiTicketDistribution.hpp"

MultiTicketDistribution::MultiTicketDistribution(TicketContainer *ticketContainer)
{
    this->ticketContainer = ticketContainer;
}

std::vector<Debt> MultiTicketDistribution::compute()
{
    definitiveList.clear();

    for (Ticket *ticket : (*ticketContainer)){
        analyzeTicket(ticket);
    }
    return definitiveList;
}

void MultiTicketDistribution::analyzeTicket(Ticket *ticket)
{
    PaymentDistribution paymentDistribution(ticket);

    int outputMessage = 0;
    std::vector<Debt> debts = paymentDistribution.compute(&outputMessage);

    if (outputMessage==PaymentDistribution::OK){

        for (Debt &debt : debts){
            analyzeDebt(debt);
        }

    }
}

void MultiTicketDistribution::analyzeDebt(Debt &debt)
{
    Debt *debtInList = lookForSameDebtInContainer(debt);
    if (!debtInList){
        definitiveList.push_back(debt);
    }
    else{
        (*debtInList)+=debt;
    }
}

Debt *MultiTicketDistribution::lookForSameDebtInContainer(const Debt &debt)
{
    for (Debt &debtFromContainer : definitiveList){
        if (debtFromContainer.compatibleWith(debt)){
            return &debtFromContainer;
        }
    }
    return nullptr;
}


