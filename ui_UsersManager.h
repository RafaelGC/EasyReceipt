/********************************************************************************
** Form generated from reading UI file 'UsersManager.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSMANAGER_H
#define UI_USERSMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UsersManager
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *userName;
    QPushButton *addBtn;
    QPushButton *deleteBtn;
    QListWidget *usersList;

    void setupUi(QDialog *UsersManager)
    {
        if (UsersManager->objectName().isEmpty())
            UsersManager->setObjectName(QStringLiteral("UsersManager"));
        UsersManager->resize(288, 224);
        verticalLayout = new QVBoxLayout(UsersManager);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(UsersManager);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        userName = new QLineEdit(UsersManager);
        userName->setObjectName(QStringLiteral("userName"));

        horizontalLayout_2->addWidget(userName);

        addBtn = new QPushButton(UsersManager);
        addBtn->setObjectName(QStringLiteral("addBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addBtn->sizePolicy().hasHeightForWidth());
        addBtn->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addBtn->setIcon(icon);
        addBtn->setAutoDefault(false);

        horizontalLayout_2->addWidget(addBtn);

        deleteBtn = new QPushButton(UsersManager);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteBtn->setIcon(icon1);
        deleteBtn->setAutoDefault(false);

        horizontalLayout_2->addWidget(deleteBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        usersList = new QListWidget(UsersManager);
        usersList->setObjectName(QStringLiteral("usersList"));

        verticalLayout->addWidget(usersList);


        retranslateUi(UsersManager);

        QMetaObject::connectSlotsByName(UsersManager);
    } // setupUi

    void retranslateUi(QDialog *UsersManager)
    {
        UsersManager->setWindowTitle(QApplication::translate("UsersManager", "Gestor de perfiles", 0));
        label->setText(QApplication::translate("UsersManager", "Nombre", 0));
        addBtn->setText(QString());
        deleteBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UsersManager: public Ui_UsersManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSMANAGER_H
