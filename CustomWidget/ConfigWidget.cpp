#include "ConfigWidget.hpp"

ConfigWidget::ConfigWidget(Config *config, QWidget *parent) :
    QDialog(parent),ui(new Ui::Config){
    ui->setupUi(this);
    this->config = config;

    (*config) = dbInterface.loadConfig();

    this->setWindowTitle(tr("Configuración"));
    ui->comboBox->setCurrentText(config->getMonetarySymbol());

    if (config->getOrder()==Config::SYMBOL_AFTER_AMOUNT){
        ui->afterRd->setChecked(true);
    }
    else{
        ui->beforeRd->setChecked(true);
    }

    QObject::connect(ui->buttons,SIGNAL(accepted()),this,SLOT(saveConfig()));

}


ConfigWidget::~ConfigWidget(){
    dbInterface.close();
    delete ui;
}

void ConfigWidget::saveConfig()
{
    config->setMonetarySymbol(ui->comboBox->currentText());
    if (ui->afterRd->isChecked()){
        config->setOrder(Config::SYMBOL_AFTER_AMOUNT);
    }
    else{
        config->setOrder(Config::SYMBOL_BEFORE_AMOUNT);
    }
    dbInterface.saveConfig(*config);

    QMessageBox::information(this,tr("Aviso"),tr("Para que se apliquen los cambios debe reiniciar el programa."));

    close();
}
