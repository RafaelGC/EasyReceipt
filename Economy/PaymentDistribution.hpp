#ifndef TICKETCOSTDISTRIBUTION_HPP
#define TICKETCOSTDISTRIBUTION_HPP

#include <QDebug>

#include <vector>

#include "Economy/Ticket.hpp"
#include "Economy/Debt.hpp"
#include "Economy/Payers.hpp"

/**
 * @brief Esta clase contiene el algoritmo que calcula quién debe pagar y cuánto a
 * quienes hayan pagado la compra.
 */

class PaymentDistribution
{
private:
    Ticket *ticket;
    /**
     * @brief Usuarios que, al haber pagado, han perdido dinero.
     */
    std::vector<UserAmount> negativeUsers;
    std::vector<UserAmount> positiveUsers;
    std::vector<Debt> algorithmResult;

    bool generateNegativeUsers();
    void analyzePayer(const UserAmount &payer);
    bool paymentAndCostMatch(float amountPayed);

    void generatePositiveUsers();
    void analyzeBuyer(const QString &buyer);

    void distributionAlgorithm();
    void solveNegativeUser(UserAmount *nUser);
    void solvePositiveUser(UserAmount *pUser, UserAmount *nUser);

    void clear();

public:
    enum{OK, DISTRIBUTION_IS_ALREADY_OK, PAYED_AND_COST_DOT_NOT_MATCH};
    PaymentDistribution(Ticket *ticket);

    std::vector<Debt> compute(int *outputMessage);

};

#endif // TICKETCOSTDISTRIBUTION_HPP
