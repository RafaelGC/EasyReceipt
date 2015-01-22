/********************************************************************************
** Form generated from reading UI file 'config.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Config
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *afterRd;
    QRadioButton *beforeRd;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *updatesEnabled;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttons;

    void setupUi(QWidget *Config)
    {
        if (Config->objectName().isEmpty())
            Config->setObjectName(QStringLiteral("Config"));
        Config->resize(258, 221);
        Config->setMinimumSize(QSize(258, 0));
        verticalLayout = new QVBoxLayout(Config);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(Config);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(Config);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEditable(true);

        verticalLayout->addWidget(comboBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(Config);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        afterRd = new QRadioButton(Config);
        afterRd->setObjectName(QStringLiteral("afterRd"));

        verticalLayout_2->addWidget(afterRd);

        beforeRd = new QRadioButton(Config);
        beforeRd->setObjectName(QStringLiteral("beforeRd"));

        verticalLayout_2->addWidget(beforeRd);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        groupBox = new QGroupBox(Config);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        updatesEnabled = new QCheckBox(groupBox);
        updatesEnabled->setObjectName(QStringLiteral("updatesEnabled"));

        verticalLayout_3->addWidget(updatesEnabled);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttons = new QDialogButtonBox(Config);
        buttons->setObjectName(QStringLiteral("buttons"));
        buttons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttons);


        retranslateUi(Config);
        QObject::connect(buttons, SIGNAL(rejected()), Config, SLOT(close()));

        QMetaObject::connectSlotsByName(Config);
    } // setupUi

    void retranslateUi(QWidget *Config)
    {
        Config->setWindowTitle(QApplication::translate("Config", "Form", 0));
        label->setText(QApplication::translate("Config", "S\303\255mbolo monetario", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Config", "\342\202\254", 0)
         << QApplication::translate("Config", "$", 0)
         << QApplication::translate("Config", "\302\243", 0)
        );
        label_2->setText(QApplication::translate("Config", "El s\303\255mbolo aparecer\303\241", 0));
#ifndef QT_NO_TOOLTIP
        afterRd->setToolTip(QApplication::translate("Config", "<html><head/><body><p>Por ejemplo: 50\342\202\254</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        afterRd->setText(QApplication::translate("Config", "despu\303\251s de la cifra.", 0));
#ifndef QT_NO_TOOLTIP
        beforeRd->setToolTip(QApplication::translate("Config", "<html><head/><body><p>Por ejemplo: $50</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        beforeRd->setText(QApplication::translate("Config", "antes de la cifra.", 0));
        groupBox->setTitle(QApplication::translate("Config", "\302\277Notificar actualizaciones?", 0));
        updatesEnabled->setText(QApplication::translate("Config", "Notificar actualizaciones", 0));
    } // retranslateUi

};

namespace Ui {
    class Config: public Ui_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
