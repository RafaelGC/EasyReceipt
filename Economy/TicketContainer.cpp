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

Ticket *TicketContainer::addTicket(QString ticketName, bool setCurrent)
{
    for (unsigned int i = 0; i<tickets.size(); i++){
        if (tickets[i]->getName()==ticketName){
            return nullptr;
        }
    }

    Ticket *ticket = new Ticket(ticketName);
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

Ticket *TicketContainer::getByName(QString ticketName){
    for (unsigned int i = 0; i<tickets.size(); i++){
        if (tickets[i]->getName()==ticketName){
            return tickets[i];
        }
    }

    return nullptr;
}

void TicketContainer::setCurrentTicket(Ticket *ticket){
    this->currentTicket = ticket;
}

Ticket *TicketContainer::ticketAt(int index){
    return tickets[index];
}

unsigned int TicketContainer::ticketsAmount(){
    return tickets.size();
}

float TicketContainer::getTotalSpentBy(QString name)
{
    float acumulator = 0;
    for (unsigned int i=0; i<tickets.size(); i++){
        Ticket *ticket = tickets[i];
        acumulator+= ticket->getPurchasePriceOf(name);
    }
    return acumulator;
}
