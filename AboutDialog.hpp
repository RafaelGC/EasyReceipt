#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include <QDialog>

#include "ui_aboutform.h"

class AboutDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::AboutForm *ui;
public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();
signals:

public slots:

};

#endif // ABOUTDIALOG_HPP
