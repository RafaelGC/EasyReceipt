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
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayersSelectorForm
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *totalPrice;
    QGroupBox *payersGroupBox;
    QGroupBox *payoutGroupBox;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *backBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *fileBtn;

    void setupUi(QWidget *PlayersSelectorForm)
    {
        if (PlayersSelectorForm->objectName().isEmpty())
            PlayersSelectorForm->setObjectName(QStringLiteral("PlayersSelectorForm"));
        PlayersSelectorForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(PlayersSelectorForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(PlayersSelectorForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        totalPrice = new QLabel(groupBox);
        totalPrice->setObjectName(QStringLiteral("totalPrice"));

        verticalLayout_2->addWidget(totalPrice);


        verticalLayout->addWidget(groupBox);

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

        fileBtn = new QPushButton(PlayersSelectorForm);
        fileBtn->setObjectName(QStringLiteral("fileBtn"));

        horizontalLayout_8->addWidget(fileBtn);


        verticalLayout->addLayout(horizontalLayout_8);


        retranslateUi(PlayersSelectorForm);

        QMetaObject::connectSlotsByName(PlayersSelectorForm);
    } // setupUi

    void retranslateUi(QWidget *PlayersSelectorForm)
    {
        PlayersSelectorForm->setWindowTitle(QApplication::translate("PlayersSelectorForm", "Form", 0));
        groupBox->setTitle(QApplication::translate("PlayersSelectorForm", "Gasto total", 0));
        totalPrice->setText(QApplication::translate("PlayersSelectorForm", "0", 0));
        payersGroupBox->setTitle(QApplication::translate("PlayersSelectorForm", "\302\277Qui\303\251n paga?", 0));
        payoutGroupBox->setTitle(QApplication::translate("PlayersSelectorForm", "Reparto", 0));
        backBtn->setText(QApplication::translate("PlayersSelectorForm", "Atr\303\241s", 0));
        fileBtn->setText(QApplication::translate("PlayersSelectorForm", "Archivar", 0));
    } // retranslateUi

};

namespace Ui {
    class PlayersSelectorForm: public Ui_PlayersSelectorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYERSSELECTOR_H
