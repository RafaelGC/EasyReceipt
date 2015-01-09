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
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
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
        payersGroupBox->setFlat(false);
        payersGroupBox->setCheckable(false);

        verticalLayout->addWidget(payersGroupBox);

        payoutGroupBox = new QGroupBox(PlayersSelectorForm);
        payoutGroupBox->setObjectName(QStringLiteral("payoutGroupBox"));

        verticalLayout->addWidget(payoutGroupBox);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        backBtn = new QPushButton(PlayersSelectorForm);
        backBtn->setObjectName(QStringLiteral("backBtn"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/go-back.png"), QSize(), QIcon::Normal, QIcon::Off);
        backBtn->setIcon(icon);
        backBtn->setIconSize(QSize(25, 25));

        verticalLayout_3->addWidget(backBtn);


        horizontalLayout_8->addLayout(verticalLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        fileBtn = new QPushButton(PlayersSelectorForm);
        fileBtn->setObjectName(QStringLiteral("fileBtn"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/tick.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileBtn->setIcon(icon1);
        fileBtn->setIconSize(QSize(32, 32));

        horizontalLayout_8->addWidget(fileBtn);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalLayout->setStretch(1, 1);

        retranslateUi(PlayersSelectorForm);

        QMetaObject::connectSlotsByName(PlayersSelectorForm);
    } // setupUi

    void retranslateUi(QWidget *PlayersSelectorForm)
    {
        PlayersSelectorForm->setWindowTitle(QApplication::translate("PlayersSelectorForm", "Form", 0));
        groupBox->setTitle(QApplication::translate("PlayersSelectorForm", "Gasto total", 0));
        totalPrice->setText(QApplication::translate("PlayersSelectorForm", "0", 0));
#ifndef QT_NO_TOOLTIP
        payersGroupBox->setToolTip(QApplication::translate("PlayersSelectorForm", "<html><head/><body><p>\302\277Qui\303\251n ha pagado la compra? Escribe cu\303\241nto ha pagado cada usuario (lo puedes dejar en blanco si no ha pagado nada). Esto puede resultar \303\272til si hay m\303\241s de un ticket pendiente o si, por cualquier motivo, la compra la pagaron varios.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        payersGroupBox->setTitle(QApplication::translate("PlayersSelectorForm", "\302\277Qui\303\251n paga?", 0));
        payoutGroupBox->setTitle(QApplication::translate("PlayersSelectorForm", "Reparto", 0));
        backBtn->setText(QString());
        fileBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PlayersSelectorForm: public Ui_PlayersSelectorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYERSSELECTOR_H
