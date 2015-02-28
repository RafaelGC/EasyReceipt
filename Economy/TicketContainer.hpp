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

    bool addTicket(Ticket *ticket);
    Ticket *createTicket(QString ticketName, bool setCurrent=false);

    void deleteTicket(QString ticketName);
    void deleteTicket(Ticket *ticket);

    Ticket *getCurrentTicket();
    Ticket *getByName(QString ticketName);
    void setCurrentTicket(Ticket *ticket);

    Ticket* &ticketAt(int index);
    Ticket* &operator[](int index);

    unsigned int count();

    QString validateName(const QString &ticketName);

    float getTotalSpentBy(QString name);
    QStringList getTicketNamesList() const;
};

//Para hacer compatible la clase con el for de rango.
Ticket* *begin(TicketContainer &ticketContainer);
Ticket* *end(TicketContainer &ticketContainer);

#endif // TICKETCONTAINER_HPP
