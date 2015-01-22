#include "AboutDialog.hpp"

AboutDialog::AboutDialog(Config *config, QWidget *parent) :
    QDialog(parent), ui(new Ui::AboutForm)
{
    ui->setupUi(this);

    ui->version->setText(config->getVersion().toString());

    this->setWindowTitle(tr("Sobre..."));
    this->setFixedSize(374,263);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}
