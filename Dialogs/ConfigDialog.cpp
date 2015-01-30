#include "ConfigDialog.hpp"

ConfigDialog::ConfigDialog(Config *config, QWidget *parent) :
    QDialog(parent),ui(new Ui::Config){
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icons/wrench.png"));

    this->config = config;

    //IDIOMAS SOPORTADOS
    ui->language->addItem(tr("Español"),QLocale::Spanish);
    ui->language->addItem(tr("Inglés"),QLocale::English);

    this->setWindowTitle(tr("Configuración"));
    ui->comboBox->setCurrentText(config->getMonetarySymbol());

    if (config->getOrder()==Config::SYMBOL_AFTER_AMOUNT){
        ui->afterRd->setChecked(true);
    }
    else{
        ui->beforeRd->setChecked(true);
    }

    if (config->getUpdatesEnabled()){
        ui->updatesEnabled->setChecked(true);
    }
    else{
        ui->updatesEnabled->setChecked(false);
    }

    if (config->getLanguage()==QLocale::Spanish){
        ui->language->setCurrentIndex(0);
    }
    else{
        ui->language->setCurrentIndex(1);
    }

    QObject::connect(ui->buttons,SIGNAL(accepted()),this,SLOT(saveConfig()));

}


ConfigDialog::~ConfigDialog(){
    delete ui;
}

void ConfigDialog::saveConfig()
{
    config->setMonetarySymbol(ui->comboBox->currentText());
    if (ui->afterRd->isChecked()){
        config->setOrder(Config::SYMBOL_AFTER_AMOUNT);
    }
    else{
        config->setOrder(Config::SYMBOL_BEFORE_AMOUNT);
    }

    config->setUpdatesEnabled(ui->updatesEnabled->isChecked());

    config->setLanguage(ui->language->currentData(Qt::UserRole).toInt());

    QMessageBox::information(this,tr("Aviso"),tr("Para que se apliquen los cambios debe reiniciar el programa."));

    close();
}
