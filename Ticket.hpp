#ifndef TICKET_HPP
#define TICKET_HPP

#include <string>
#include <vector>

class Ticket
{
public:
    Ticket();

    float getTotalCost();
    void addItem(float cost, std::vector<std::string>buyers);
    void getCostOf(std::string name);

};

#endif // TICKET_HPP
