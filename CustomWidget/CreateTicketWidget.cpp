#include "CreateTicketWidget.hpp"

CreateTicketWidget::CreateTicketWidget(QWidget *parent) :
    QWidget(parent),ui(new Ui::Form){
    ui->setupUi(this);
}

CreateTicketWidget::~CreateTicketWidget()
{
    delete ui;
}
