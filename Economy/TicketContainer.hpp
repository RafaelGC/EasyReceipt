#ifndef TICKETCONTAINER_HPP
#define TICKETCONTAINER_HPP

#include <vector>

#include "Economy/Ticket.hpp"
#include "Economy/Product.hpp"

class TicketContainer
{
private:
    std::vector<Ticket>tickets;
public:
    TicketContainer();
};

#endif // TICKETCONTAINER_HPP
