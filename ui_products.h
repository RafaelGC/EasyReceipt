/********************************************************************************
** Form generated from reading UI file 'products.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTS_H
#define UI_PRODUCTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TicketManagerForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topInputLayout;
    QHBoxLayout *infoLayout;
    QGroupBox *historialGroupBox;
    QVBoxLayout *verticalLayout_2;
    QListWidget *historialList;
    QHBoxLayout *horizontalLayout;
    QPushButton *deleteSelection;
    QPushButton *upSelection;
    QGroupBox *repartoGroupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *userListLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *totalLabel;
    QPushButton *clearButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *next;

    void setupUi(QWidget *TicketManagerForm)
    {
        if (TicketManagerForm->objectName().isEmpty())
            TicketManagerForm->setObjectName(QStringLiteral("TicketManagerForm"));
        TicketManagerForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(TicketManagerForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topInputLayout = new QHBoxLayout();
        topInputLayout->setObjectName(QStringLiteral("topInputLayout"));

        verticalLayout->addLayout(topInputLayout);

        infoLayout = new QHBoxLayout();
        infoLayout->setSpacing(6);
        infoLayout->setObjectName(QStringLiteral("infoLayout"));
        infoLayout->setContentsMargins(0, -1, -1, -1);
        historialGroupBox = new QGroupBox(TicketManagerForm);
        historialGroupBox->setObjectName(QStringLiteral("historialGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(historialGroupBox->sizePolicy().hasHeightForWidth());
        historialGroupBox->setSizePolicy(sizePolicy);
        historialGroupBox->setFlat(false);
        historialGroupBox->setCheckable(false);
        verticalLayout_2 = new QVBoxLayout(historialGroupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        historialList = new QListWidget(historialGroupBox);
        historialList->setObjectName(QStringLiteral("historialList"));

        verticalLayout_2->addWidget(historialList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        deleteSelection = new QPushButton(historialGroupBox);
        deleteSelection->setObjectName(QStringLiteral("deleteSelection"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(deleteSelection->sizePolicy().hasHeightForWidth());
        deleteSelection->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteSelection->setIcon(icon);
        deleteSelection->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(deleteSelection);

        upSelection = new QPushButton(historialGroupBox);
        upSelection->setObjectName(QStringLiteral("upSelection"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(upSelection->sizePolicy().hasHeightForWidth());
        upSelection->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(upSelection);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);

        infoLayout->addWidget(historialGroupBox);

        repartoGroupBox = new QGroupBox(TicketManagerForm);
        repartoGroupBox->setObjectName(QStringLiteral("repartoGroupBox"));
        sizePolicy.setHeightForWidth(repartoGroupBox->sizePolicy().hasHeightForWidth());
        repartoGroupBox->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(repartoGroupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        userListLayout = new QVBoxLayout();
        userListLayout->setObjectName(QStringLiteral("userListLayout"));

        verticalLayout_3->addLayout(userListLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(25);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(repartoGroupBox);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        QFont font;
        font.setPointSize(14);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        totalLabel = new QLabel(repartoGroupBox);
        totalLabel->setObjectName(QStringLiteral("totalLabel"));
        totalLabel->setFont(font);
        totalLabel->setCursor(QCursor(Qt::IBeamCursor));
        totalLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_2->addWidget(totalLabel);


        verticalLayout_3->addLayout(horizontalLayout_2);

        clearButton = new QPushButton(repartoGroupBox);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        verticalLayout_3->addWidget(clearButton);


        infoLayout->addWidget(repartoGroupBox);


        verticalLayout->addLayout(infoLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        cancelBtn = new QPushButton(TicketManagerForm);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout_3->addWidget(cancelBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        next = new QPushButton(TicketManagerForm);
        next->setObjectName(QStringLiteral("next"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(next->sizePolicy().hasHeightForWidth());
        next->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(next);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(1, 1);

        retranslateUi(TicketManagerForm);

        QMetaObject::connectSlotsByName(TicketManagerForm);
    } // setupUi

    void retranslateUi(QWidget *TicketManagerForm)
    {
        TicketManagerForm->setWindowTitle(QApplication::translate("TicketManagerForm", "Form", 0));
        historialGroupBox->setTitle(QApplication::translate("TicketManagerForm", "Historial", 0));
        deleteSelection->setText(QString());
        upSelection->setText(QApplication::translate("TicketManagerForm", "Copiar selecci\303\263n", 0));
        repartoGroupBox->setTitle(QApplication::translate("TicketManagerForm", "Reparto", 0));
        label->setText(QApplication::translate("TicketManagerForm", "Total:", 0));
        totalLabel->setText(QApplication::translate("TicketManagerForm", "0", 0));
        clearButton->setText(QApplication::translate("TicketManagerForm", "Limpiar todo", 0));
        cancelBtn->setText(QApplication::translate("TicketManagerForm", "Cancelar", 0));
        next->setText(QApplication::translate("TicketManagerForm", "Siguiente", 0));
    } // retranslateUi

};

namespace Ui {
    class TicketManagerForm: public Ui_TicketManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTS_H
