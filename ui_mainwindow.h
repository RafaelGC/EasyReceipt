/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExportHtml;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionUsersManager;
    QAction *actionEliminar_perfil;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_4;
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
    QPushButton *next;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QMenu *menuSobre;
    QMenu *menuPerfiles;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(533, 453);
        MainWindow->setWindowOpacity(1);
        MainWindow->setAnimated(true);
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionExportHtml = new QAction(MainWindow);
        actionExportHtml->setObjectName(QStringLiteral("actionExportHtml"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionUsersManager = new QAction(MainWindow);
        actionUsersManager->setObjectName(QStringLiteral("actionUsersManager"));
        actionEliminar_perfil = new QAction(MainWindow);
        actionEliminar_perfil->setObjectName(QStringLiteral("actionEliminar_perfil"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_4 = new QVBoxLayout(page);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        topInputLayout = new QHBoxLayout();
        topInputLayout->setObjectName(QStringLiteral("topInputLayout"));

        verticalLayout_4->addLayout(topInputLayout);

        infoLayout = new QHBoxLayout();
        infoLayout->setSpacing(6);
        infoLayout->setObjectName(QStringLiteral("infoLayout"));
        infoLayout->setContentsMargins(0, -1, -1, -1);
        historialGroupBox = new QGroupBox(page);
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

        horizontalLayout->addWidget(deleteSelection);

        upSelection = new QPushButton(historialGroupBox);
        upSelection->setObjectName(QStringLiteral("upSelection"));

        horizontalLayout->addWidget(upSelection);


        verticalLayout_2->addLayout(horizontalLayout);


        infoLayout->addWidget(historialGroupBox);

        repartoGroupBox = new QGroupBox(page);
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
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
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


        verticalLayout_4->addLayout(infoLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        next = new QPushButton(page);
        next->setObjectName(QStringLiteral("next"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(next->sizePolicy().hasHeightForWidth());
        next->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(next);


        verticalLayout_4->addLayout(horizontalLayout_3);

        stackedWidget->addWidget(page);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 533, 21));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName(QStringLiteral("menuArchivo"));
        menuSobre = new QMenu(menubar);
        menuSobre->setObjectName(QStringLiteral("menuSobre"));
        menuPerfiles = new QMenu(menubar);
        menuPerfiles->setObjectName(QStringLiteral("menuPerfiles"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuArchivo->menuAction());
        menubar->addAction(menuPerfiles->menuAction());
        menubar->addAction(menuSobre->menuAction());
        menuArchivo->addAction(actionExportHtml);
        menuArchivo->addSeparator();
        menuArchivo->addAction(actionExit);
        menuSobre->addAction(actionAbout);
        menuPerfiles->addAction(actionUsersManager);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Reparto - BETA", 0));
        actionExportHtml->setText(QApplication::translate("MainWindow", "Exportar a HTML", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Salir", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "Sobre...", 0));
        actionUsersManager->setText(QApplication::translate("MainWindow", "Gestionar perfiles", 0));
        actionEliminar_perfil->setText(QApplication::translate("MainWindow", "Eliminar perfil", 0));
        historialGroupBox->setTitle(QApplication::translate("MainWindow", "Historial", 0));
        deleteSelection->setText(QApplication::translate("MainWindow", "Eliminar selecci\303\263n", 0));
        upSelection->setText(QApplication::translate("MainWindow", "Subir selecci\303\263n", 0));
        repartoGroupBox->setTitle(QApplication::translate("MainWindow", "Reparto", 0));
        label->setText(QApplication::translate("MainWindow", "Total:", 0));
        totalLabel->setText(QApplication::translate("MainWindow", "0", 0));
        clearButton->setText(QApplication::translate("MainWindow", "Limpiar todo", 0));
        next->setText(QApplication::translate("MainWindow", "Siguiente", 0));
        menuArchivo->setTitle(QApplication::translate("MainWindow", "Archivo", 0));
        menuSobre->setTitle(QApplication::translate("MainWindow", "Sobre", 0));
        menuPerfiles->setTitle(QApplication::translate("MainWindow", "Perfiles", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
