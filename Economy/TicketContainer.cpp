#include "TicketContainer.hpp"

TicketContainer::TicketContainer()
{
    currentTicket = nullptr;
}

TicketContainer::~TicketContainer()
{
    for (unsigned int i = 0; i<tickets.size(); i++){
        delete tickets.at(i);
    }
    tickets.clear();
}

Ticket *TicketContainer::addTicket(bool setCurrent)
{
    qDebug() << "Ticket added";
    qDebug() << "Tickets: " << tickets.size();
    Ticket *ticket = new Ticket();
    tickets.push_back(ticket);

    //Si no hay ningún ticket establecido, aprovechamos para
    //establecerlo.
    if (!currentTicket || setCurrent){
        currentTicket=ticket;
    }

    return ticket;
}

Ticket *TicketContainer::getCurrentTicket()
{
    return currentTicket;
}
