#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T00:51:57
#
#-------------------------------------------------

QT       += core gui sql xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reparti2
TEMPLATE = app


SOURCES += main.cpp\
    Mainwindow.cpp \
    User.cpp \
    UsersManagerDialog.cpp \
    UserContainer.cpp \
    PayerObserver.cpp \
    Persistence/HtmlExporter.cpp \
    Persistence/UserDbInterface.cpp \
    CustomWidget/PayerWidget.cpp \
    CustomWidget/HistoryWidget.cpp \
    CustomWidget/PayersSelection.cpp \
    CustomWidget/SpaceLineEdit.cpp \
    CustomWidget/PredictionLineEdit.cpp \
    Economy/Ticket.cpp \
    Economy/Product.cpp \
    Economy/TicketContainer.cpp \
    Economy/Debt.cpp \
    CustomWidget/CreateTicketWidget.cpp \
    CustomWidget/ManageTicketWidget.cpp \
    CustomWidget/TotalPayout.cpp \
    CustomWidget/ConfigWidget.cpp \
    Persistence/ConfigDbInterface.cpp \
    Config.cpp \
    AboutDialog.cpp \
    Persistence/XmlManager.cpp \
    Version.cpp \
    UpdateManager.cpp \
    UpdateDialog.cpp

HEADERS  += \
    User.hpp \
    UsersManagerDialog.hpp \
    UserContainer.hpp \
    PayerObserver.hpp \
    Persistence/HtmlExporter.hpp \
    Persistence/UserDbInterface.hpp \
    CustomWidget/PayerWidget.hpp \
    CustomWidget/HistoryWidget.hpp \
    CustomWidget/PayersSelection.hpp \
    CustomWidget/SpaceLineEdit.hpp \
    CustomWidget/PredictionLineEdit.hpp \
    Economy/Ticket.hpp \
    Economy/Product.hpp \
    Economy/TicketContainer.hpp \
    Mainwindow.hpp \
    Economy/Debt.hpp \
    CustomWidget/CreateTicketWidget.hpp \
    CustomWidget/ManageTicketWidget.hpp \
    CustomWidget/TotalPayout.hpp \
    CustomWidget/ConfigWidget.hpp \
    Persistence/ConfigDbInterface.hpp \
    Config.hpp \
    AboutDialog.hpp \
    Persistence/XmlManager.hpp \
    Version.hpp \
    UpdateManager.hpp \
    UpdateDialog.hpp

FORMS    += mainwindow.ui \
    UsersManager.ui \
    payersselector.ui \
    ticketpanel.ui \
    products.ui \
    finalpayout.ui \
    config.ui \
    aboutform.ui \
    updatedialog.ui

CONFIG += c++11

RC_FILE = resource.rc

RESOURCES += \
    resources.qrc
TRANSLATIONS += prueba.ls
OTHER_FILES += \
    resource.rc
