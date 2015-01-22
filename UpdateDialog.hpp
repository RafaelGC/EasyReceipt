#ifndef UPDATEDIALOG_HPP
#define UPDATEDIALOG_HPP

#include <QDialog>
#include "Version.hpp"
#include "ui_updatedialog.h"
class UpdateDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::UpdateDialog *ui;
public:
    explicit UpdateDialog(QWidget *parent = 0);
    ~UpdateDialog();
    void open(const Version &version, const QString &updateLink);
signals:

public slots:

};

#endif // UPDATEDIALOG_HPP
