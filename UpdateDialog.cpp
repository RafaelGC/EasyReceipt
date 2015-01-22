#include "UpdateDialog.hpp"

UpdateDialog::UpdateDialog(QWidget *parent) :
    QDialog(parent),ui(new Ui::UpdateDialog){
    ui->setupUi(this);


}

UpdateDialog::~UpdateDialog(){
    delete ui;
}

void UpdateDialog::open(const Version & version, const QString &updateLink){
    ui->updateVersion->setText(ui->updateVersion->text().replace("%1",version.toString()));
    ui->updateLink->setText(ui->updateLink->text().replace("%1",updateLink));
    QDialog::open();
}
