#include "AboutDialog.hpp"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AboutForm)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Sobre..."));
    this->setFixedSize(374,263);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}
