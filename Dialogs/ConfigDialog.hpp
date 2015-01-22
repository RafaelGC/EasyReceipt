#ifndef CONFIGWIDGET_HPP
#define CONFIGWIDGET_HPP

#include <QDialog>
#include <QMessageBox>

#include "ui_config.h"
#include "Persistence/ConfigDbInterface.hpp"
#include "Config.hpp"

class ConfigDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::Config *ui;
    Config *config;

public:
    explicit ConfigDialog(Config *config, QWidget *parent = 0);
    ~ConfigDialog();

signals:
private slots:
    void saveConfig();
public slots:

};

#endif // CONFIGWIDGET_HPP
