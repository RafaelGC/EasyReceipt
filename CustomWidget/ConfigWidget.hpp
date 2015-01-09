#ifndef CONFIGWIDGET_HPP
#define CONFIGWIDGET_HPP

#include <QDialog>
#include <QMessageBox>

#include "ui_config.h"
#include "Persistence/ConfigDbInterface.hpp"
#include "Config.hpp"

class ConfigWidget : public QDialog
{
    Q_OBJECT
private:
    Ui::Config *ui;
    ConfigDbInterface dbInterface;
    Config *config;

public:
    explicit ConfigWidget(Config *config, QWidget *parent = 0);
    ~ConfigWidget();

signals:
private slots:
    void saveConfig();
public slots:

};

#endif // CONFIGWIDGET_HPP
