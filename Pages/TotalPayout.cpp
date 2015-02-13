#include "TotalPayout.hpp"

TotalPayout::TotalPayout(TicketContainer*ticketContainer, Config *config, QWidget *parent) :
    QWidget(parent), ui(new Ui::FinalPayout){
    ui->setupUi(this);
    this->config = config;

    this->ticketContainer = ticketContainer;

    QObject::connect(ui->backBtn,SIGNAL(clicked()),this,SIGNAL(goBack()));
}

TotalPayout::~TotalPayout()
{
    delete ui;
}


void TotalPayout::showEvent(QShowEvent *){
    std::vector<Debt>debtList;

    //Para cada ticket.
    for (unsigned int i=0; i<ticketContainer->ticketsAmount(); i++){
        Ticket *ticket = ticketContainer->ticketAt(i);

        int message = -1;
        //Hago el cálculo de reparto idividual.
        std::vector<Debt>d = ticket->computePayout(&message);
        if (message==Ticket::SUCCESS){
            for (unsigned int j=0; j<d.size(); j++){
                bool found = false;
                for (unsigned int k=0; k<debtList.size(); k++){
                    if (d[j]==debtList[k]){
                        debtList[k].setAmount(debtList[k].getAmount()+d[k].getAmount());
                        found = true;
                    }
                    else if (d[j].isSwapped(debtList[k])){
                        debtList[k].setAmount(debtList[k].getAmount()-d[k].getAmount());
                        found = true;
                    }
                    if (found){
                        //debtList[k].swapIfNeeded();
                        break;
                    }
                }
                if (!found){
                    debtList.push_back(d[j]);
                }
            }
        }
    }

    ui->totalPayoutText->clear();

    for (unsigned int i=0; i<debtList.size(); i++){
        if (debtList[i].getAmount()!=0){
            ui->totalPayoutText->appendPlainText(QString(tr("%1 debe pagar %2 a %3")).arg(debtList[i].getDebtor())
                                             .arg(config->constructMoney(debtList[i].getAmount(true))).arg(debtList[i].getCreditor())
                                             );
        }
    }

    if (ui->totalPayoutText->toPlainText().isEmpty()){
        ui->totalPayoutText->setPlainText(tr("Nada pendiente."));
    }


}
