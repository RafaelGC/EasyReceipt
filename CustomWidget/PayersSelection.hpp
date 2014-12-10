#ifndef PAYERSSELECTION_HPP
#define PAYERSSELECTION_HPP

#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGridLayout>

#include "PayerObserver.hpp"
#include "UserContainer.hpp"
#include "ui_payersselector.h"

class PayersSelection : public QWidget
{
    Q_OBJECT
private:
    Ui::PlayersSelectorForm *ui;
    UserContainer*userContainer;
    QGridLayout *payersLayout;

    std::vector<PayerObserver*> payerObservers;

    void clearPayerObservers();
public:
    explicit PayersSelection(UserContainer *userContainer,QWidget *parent = 0);
    ~PayersSelection();
private slots:
    void payerChanged(QString payerName, bool cheked, float amount);
public slots:
    void updatePayers();
signals:
    void nextPanel();
    void previousPanel();

};

#endif // PAYERSSELECTION_HPP
