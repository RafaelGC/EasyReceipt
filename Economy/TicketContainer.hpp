#ifndef TICKETCONTAINER_HPP
#define TICKETCONTAINER_HPP

#include <vector>

#include "Economy/Ticket.hpp"
#include "Economy/Product.hpp"

class TicketContainer
{
private:
    std::vector<Ticket*>tickets;
    //Dirección del ticket con el que se está trabajando actualmente.
    //Debería estar también contenido en el vector.
    Ticket *currentTicket;
public:
    TicketContainer();
    ~TicketContainer();

    Ticket *addTicket();
    Ticket *getCurrentTicket();
};

#endif // TICKETCONTAINER_HPP
