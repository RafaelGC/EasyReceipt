/********************************************************************************
** Form generated from reading UI file 'finalpayout.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINALPAYOUT_H
#define UI_FINALPAYOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FinalPayout
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *totalPayoutText;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *backBtn;

    void setupUi(QWidget *FinalPayout)
    {
        if (FinalPayout->objectName().isEmpty())
            FinalPayout->setObjectName(QStringLiteral("FinalPayout"));
        FinalPayout->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(FinalPayout);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(FinalPayout);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        totalPayoutText = new QPlainTextEdit(groupBox);
        totalPayoutText->setObjectName(QStringLiteral("totalPayoutText"));
        totalPayoutText->setEnabled(true);
        totalPayoutText->setReadOnly(true);

        verticalLayout->addWidget(totalPayoutText);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        backBtn = new QPushButton(FinalPayout);
        backBtn->setObjectName(QStringLiteral("backBtn"));

        horizontalLayout->addWidget(backBtn);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(FinalPayout);

        QMetaObject::connectSlotsByName(FinalPayout);
    } // setupUi

    void retranslateUi(QWidget *FinalPayout)
    {
        FinalPayout->setWindowTitle(QApplication::translate("FinalPayout", "Form", 0));
#ifndef QT_NO_TOOLTIP
        groupBox->setToolTip(QApplication::translate("FinalPayout", "<html><head/><body><p>Aqu\303\255 se muestra el pago pendiente de cada uno de los usuarios teniendo en cuenta todos los tickets.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("FinalPayout", "Reparto total", 0));
        backBtn->setText(QApplication::translate("FinalPayout", "Volver", 0));
    } // retranslateUi

};

namespace Ui {
    class FinalPayout: public Ui_FinalPayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINALPAYOUT_H
