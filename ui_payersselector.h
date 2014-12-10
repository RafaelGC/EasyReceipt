/********************************************************************************
** Form generated from reading UI file 'payersselector.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAYERSSELECTOR_H
#define UI_PAYERSSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayersSelectorForm
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *payersGroupBox;
    QGroupBox *payoutGroupBox;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *backBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;

    void setupUi(QWidget *PlayersSelectorForm)
    {
        if (PlayersSelectorForm->objectName().isEmpty())
            PlayersSelectorForm->setObjectName(QStringLiteral("PlayersSelectorForm"));
        PlayersSelectorForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(PlayersSelectorForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        payersGroupBox = new QGroupBox(PlayersSelectorForm);
        payersGroupBox->setObjectName(QStringLiteral("payersGroupBox"));

        verticalLayout->addWidget(payersGroupBox);

        payoutGroupBox = new QGroupBox(PlayersSelectorForm);
        payoutGroupBox->setObjectName(QStringLiteral("payoutGroupBox"));

        verticalLayout->addWidget(payoutGroupBox);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        backBtn = new QPushButton(PlayersSelectorForm);
        backBtn->setObjectName(QStringLiteral("backBtn"));

        horizontalLayout_8->addWidget(backBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(PlayersSelectorForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_8->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_8);


        retranslateUi(PlayersSelectorForm);

        QMetaObject::connectSlotsByName(PlayersSelectorForm);
    } // setupUi

    void retranslateUi(QWidget *PlayersSelectorForm)
    {
        PlayersSelectorForm->setWindowTitle(QApplication::translate("PlayersSelectorForm", "Form", 0));
        payersGroupBox->setTitle(QApplication::translate("PlayersSelectorForm", "\302\277Quien paga?", 0));
        payoutGroupBox->setTitle(QApplication::translate("PlayersSelectorForm", "Reparto", 0));
        backBtn->setText(QApplication::translate("PlayersSelectorForm", "Atr\303\241s", 0));
        pushButton_2->setText(QApplication::translate("PlayersSelectorForm", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class PlayersSelectorForm: public Ui_PlayersSelectorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYERSSELECTOR_H
