#include "PaymentDistribution.hpp"
#include <math.h>

PaymentDistribution::PaymentDistribution(Ticket *ticket)
{
    this->ticket = ticket;
}

std::vector<Debt> PaymentDistribution::compute(int *outputMessage)
{
    if (generateNegativeUsers()){
        generatePositiveUsers();
        distributionAlgorithm();

        if (algorithmResult.size()==0){
            (*outputMessage) = DISTRIBUTION_IS_ALREADY_OK;
        }
        else{
            (*outputMessage) = OK;
        }
    }
    else{
        (*outputMessage) = PAYED_AND_COST_DOT_NOT_MATCH;
    }

    std::vector<Debt> copy = algorithmResult;

    clear();

    return copy;
}

bool PaymentDistribution::generateNegativeUsers()
{
    Payers * payers = ticket->getPayers();
    float payedCounter = 0.f;

    for (unsigned int i = 0; i<payers->countPayers(); ++i)
    {
        UserAmount payer = (*payers)[i];
        payedCounter += payer.getAmount();
        analyzePayer(payer);

    }

    return paymentAndCostMatch(payedCounter);
}

void PaymentDistribution::analyzePayer(const UserAmount &payer)
{
    float net = ticket->getPurchasePriceOf(payer.getName()) - payer.getAmount();

    /*Sólo si ha perdido dinero será un usuario negativo. Si, aun habiendo pagado
     * tiene un saldo neto positivo tendrá que pagar a alguien. Si es cero, significa
     * que ha pagado lo justo.
     * */
    if (net < 0)
    {
        //Importante remarcar que el saldo neto será POSITIVO, aunque represente una pérdida.
        negativeUsers.push_back(UserAmount(payer.getName(),-net));
    }
}

bool PaymentDistribution::paymentAndCostMatch(float amountPayed)
{
    return (fabs(amountPayed-ticket->getTotalCost())<0.0001);
}

void PaymentDistribution::generatePositiveUsers()
{
    QStringList buyers = ticket->getBuyers();

    for (QString buyer : buyers)
    {
        analyzeBuyer(buyer);
    }
}

void PaymentDistribution::analyzeBuyer(const QString &buyer)
{
    float buyed = ticket->getPurchasePriceOf(buyer);
    if (ticket->getPayers()->isPayer(buyer)){
        float amountPayed = ticket->getPayers()->payedBy(buyer);
        float net = buyed - amountPayed;

        if (!(fabs(net)<0.0001)){ //Si NO es cero
            //Sólo nos interesa los usuarios positivos.
            if (net>0){
                positiveUsers.push_back(UserAmount(buyer,net));
            }
        }

    }
    else{
        positiveUsers.push_back(UserAmount(buyer,buyed));
    }
}

void PaymentDistribution::distributionAlgorithm()
{
    for (auto nUserIt = negativeUsers.begin(); nUserIt!=negativeUsers.end(); ++nUserIt){

        UserAmount* nUser = &(*nUserIt);

        solveNegativeUser(nUser);
    }
}

void PaymentDistribution::solveNegativeUser(UserAmount *nUser)
{
    for (auto pUserIt = positiveUsers.begin(); pUserIt!=positiveUsers.end(); ++pUserIt){

        UserAmount *pUser = &(*pUserIt);

        solvePositiveUser(pUser, nUser);

        if (fabs(nUser->getAmount())<0.0001){
            break;
        }

    }
}

void PaymentDistribution::solvePositiveUser(UserAmount *pUser, UserAmount *nUser)
{
    float decr = std::min(pUser->getAmount(),nUser->getAmount());

    pUser->setAmount(pUser->getAmount()-decr);
    nUser->setAmount(nUser->getAmount()-decr);

    algorithmResult.push_back(Debt(pUser->getName(),decr,nUser->getName()));
}

void PaymentDistribution::clear()
{
    positiveUsers.clear();
    negativeUsers.clear();
    algorithmResult.clear();
}
