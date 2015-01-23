#include "NotesWindow.hpp"

NotesWindow::NotesWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::NotesWindow){
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,2);

    orderByName = new SmallButton(this);
    orderByName->setText(tr("Nombre"));
    orderByName->setCheckable(true);
    orderByName->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    ui->horizontalLayout->addWidget(orderByName);

    orderByDate = new SmallButton(this);
    orderByDate->setText(tr("Fecha"));
    orderByDate->setCheckable(true);
    orderByDate->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    ui->horizontalLayout->addWidget(orderByDate);

    orderByName->setChecked(true);


    QObject::connect(orderByName,SIGNAL(clicked()),this,SLOT(orderByNameClicked()));
    QObject::connect(orderByDate,SIGNAL(clicked()),this,SLOT(orderByDateClicked()));

}

NotesWindow::~NotesWindow(){
    delete ui;
}

void NotesWindow::orderByNameClicked(){
    orderByDate->setChecked(!orderByName->isChecked());
}

void NotesWindow::orderByDateClicked(){
    orderByName->setChecked(!orderByDate->isChecked());
}
