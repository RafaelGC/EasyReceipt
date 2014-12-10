#include "PayersSelection.hpp"

PayersSelection::PayersSelection(UserContainer *userContainer, QWidget *parent) :
    QWidget(parent),ui(new Ui::PlayersSelectorForm)
{
    ui->setupUi(this);

    this->userContainer = userContainer;

    payersLayout = new QGridLayout(ui->payersGroupBox);
    updatePayers();

    QObject::connect(ui->backBtn,SIGNAL(clicked()),this,SIGNAL(previousPanel()));

}

PayersSelection::~PayersSelection()
{
    clearPayerObservers();
    delete ui;
}

void PayersSelection::payerChanged(QString payerName, bool cheked, float amount)
{
    //Cada vez que se realiza un cambio se debe reajustar el reparto.

    for (unsigned int i = 0; i<payerObservers.size(); i++){
    }
}

void PayersSelection::updatePayers(){
    /*Primero se eliminan toda la lista de usuarios para
     * que pueda ser generada de nuevo. */
    QLayoutItem *child;
    while ((child = payersLayout->takeAt(0)) != 0) {
        if (child->widget()){
            child->widget()->setParent(nullptr);
        }
        delete child;
    }
    clearPayerObservers();

    /*Y ahora se genera la nueva lista.*/
    unsigned int i = 0;
    for (; i<userContainer->size(); i++){
        /*Se crean dos instancias de los elementos widgets necesarios.*/
        QCheckBox *ck = new QCheckBox(userContainer->userAt(i)->getName());
        QLineEdit *td = new QLineEdit();
        /*Se añade un validador para que sólo se puedan introducir números.*/
        td->setValidator(new QDoubleValidator(0,100000,3,td));

        /*Se añaden al layout.*/
        payersLayout->addWidget(ck,i,0,1,1,Qt::AlignLeft);
        payersLayout->addWidget(td,i,1,1,1,Qt::AlignLeft);

        /*Ahora los dos elementos se almacenan en un objeto que contendrá
         * referencias a ellos y que estará pendiente de informarnos cuando
         * estos elementos se hayan sometido a alguna modificación. */

        PayerObserver *po = new PayerObserver(ck,td);

        payerObservers.push_back(po);
        QObject::connect(po,SIGNAL(payerChanged(QString,bool,float))
                         ,this,SLOT(payerChanged(QString,bool,float)));
    }
    payersLayout->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding),++i,0);
    payersLayout->setColumnStretch(1,1);
}

void PayersSelection::clearPayerObservers()
{
    for (unsigned int i=0; i<payerObservers.size(); i++){
        delete payerObservers[i];
    }
    payerObservers.clear();
}
