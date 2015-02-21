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

Ticket *TicketContainer::createTicket(QString ticketName, bool setCurrent)
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

void TicketContainer::deleteTicket(QString ticketName){
    for (unsigned int i=0; i<tickets.size(); i++){
        if (tickets[i]->getName()==ticketName){
            if (currentTicket==tickets[i]){
                currentTicket = nullptr;
            }
            delete tickets[i];
            tickets.erase(tickets.begin()+i);
        }
    }
}

void TicketContainer::deleteTicket(Ticket *ticket){
    deleteTicket(ticket->getName());
}

Ticket *TicketContainer::getCurrentTicket(){
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

Ticket* &TicketContainer::ticketAt(int index){
    return tickets[index];
}

Ticket* &TicketContainer::operator[](int index)
{
    return ticketAt(index);
}

unsigned int TicketContainer::ticketsAmount(){
    return tickets.size();
}

QString TicketContainer::validateName(const QString &ticketName){
    QString returnName = ticketName;
    //Se estudia uno a uno los tickets.
    if (getByName(ticketName)!=nullptr){
        for (int i = 1; i<365; i++){ //Número random.
            returnName = returnName.append(" (%1)").arg(i);
            if (getByName(returnName)){
                returnName = ticketName; //Se resetea.
            }
            else{
                break;
            }
        }

    }
    return returnName;
}

bool TicketContainer::addTicket(Ticket *ticket){
    if (getByName(ticket->getName())){
        return false;
    }

    tickets.push_back(ticket);
    return true;
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


Ticket **begin(TicketContainer &ticketContainer)
{
    return &ticketContainer[0];
}


Ticket **end(TicketContainer &ticketContainer)
{
    return begin(ticketContainer)+ticketContainer.ticketsAmount();
}
