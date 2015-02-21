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

    MultiTicketDistribution distribution(ticketContainer);
    std::vector<Debt> debtList = distribution.compute();

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
