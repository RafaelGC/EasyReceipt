/********************************************************************************
** Form generated from reading UI file 'ticketpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICKETPANEL_H
#define UI_TICKETPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QListWidget *ticketList;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *seeTicketBtn;
    QPushButton *deleteTicketBtn;
    QPushButton *totalPayoutBtn;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ticketName;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *addTicketBtn;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(499, 300);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        ticketList = new QListWidget(Form);
        ticketList->setObjectName(QStringLiteral("ticketList"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ticketList->sizePolicy().hasHeightForWidth());
        ticketList->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(ticketList);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        seeTicketBtn = new QPushButton(Form);
        seeTicketBtn->setObjectName(QStringLiteral("seeTicketBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(seeTicketBtn->sizePolicy().hasHeightForWidth());
        seeTicketBtn->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        seeTicketBtn->setIcon(icon);
        seeTicketBtn->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(seeTicketBtn);

        deleteTicketBtn = new QPushButton(Form);
        deleteTicketBtn->setObjectName(QStringLiteral("deleteTicketBtn"));
        sizePolicy1.setHeightForWidth(deleteTicketBtn->sizePolicy().hasHeightForWidth());
        deleteTicketBtn->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteTicketBtn->setIcon(icon1);
        deleteTicketBtn->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(deleteTicketBtn);

        totalPayoutBtn = new QPushButton(Form);
        totalPayoutBtn->setObjectName(QStringLiteral("totalPayoutBtn"));
        sizePolicy1.setHeightForWidth(totalPayoutBtn->sizePolicy().hasHeightForWidth());
        totalPayoutBtn->setSizePolicy(sizePolicy1);
        totalPayoutBtn->setMinimumSize(QSize(0, 0));
        totalPayoutBtn->setSizeIncrement(QSize(0, 0));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/money.png"), QSize(), QIcon::Normal, QIcon::Off);
        totalPayoutBtn->setIcon(icon2);
        totalPayoutBtn->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(totalPayoutBtn);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(label);

        ticketName = new QLineEdit(groupBox);
        ticketName->setObjectName(QStringLiteral("ticketName"));

        horizontalLayout_2->addWidget(ticketName);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        addTicketBtn = new QPushButton(groupBox);
        addTicketBtn->setObjectName(QStringLiteral("addTicketBtn"));

        horizontalLayout_4->addWidget(addTicketBtn);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2->setOpenExternalLinks(true);
        label_2->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse|Qt::TextBrowserInteraction|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(0, 1);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(1, 3);
        QWidget::setTabOrder(ticketName, addTicketBtn);
        QWidget::setTabOrder(addTicketBtn, ticketList);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
#ifndef QT_NO_TOOLTIP
        seeTicketBtn->setToolTip(QApplication::translate("Form", "Editar el ticket seleccionado.", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        deleteTicketBtn->setToolTip(QApplication::translate("Form", "Eliminar el ticket seleccionado.", 0));
#endif // QT_NO_TOOLTIP
        deleteTicketBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        totalPayoutBtn->setToolTip(QApplication::translate("Form", "Reparto final (teniendo en cuenta <b>todos</b> los tickets de la lista).", 0));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("Form", "Nuevo ticket", 0));
        label->setText(QApplication::translate("Form", "Nombre", 0));
#ifndef QT_NO_TOOLTIP
        ticketName->setToolTip(QApplication::translate("Form", "<html><head/><body><p>Nombre identificativo del ticket. Es una buena idea que sea la fecha en la que se realiz\303\263 la compra.</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        addTicketBtn->setText(QApplication::translate("Form", "A\303\261adir", 0));
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("Form", "Es s\303\263lo una broma.", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("Form", "<html><head/><body><p><a href=\"www.google.es\"><span style=\" text-decoration: underline; color:#0000ff;\">ALPHA-BETA PRERELEASE INDEV 1.6 UNICORNIO</span></a></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICKETPANEL_H
