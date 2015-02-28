#ifndef TICKETLOADEDLISTENER_HPP
#define TICKETLOADEDLISTENER_HPP

#include "Economy/Ticket.hpp"

class TicketLoadedListener
{
public:
    TicketLoadedListener();
    virtual void ticketLoaded(Ticket *ticket) = 0;
};

#endif // TICKETLOADEDLISTENER_HPP
