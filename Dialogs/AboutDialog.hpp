#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include <QDialog>
#include <QDebug>

#include "Version.hpp"
#include "Config.hpp"

#include "ui_aboutform.h"

class AboutDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::AboutForm *ui;
public:
    explicit AboutDialog(Config *config, QWidget *parent = 0);
    ~AboutDialog();
signals:

public slots:

};

#endif // ABOUTDIALOG_HPP
