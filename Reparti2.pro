#-------------------------------------------------
#
# Project created by QtCreator 2014-11-03T00:51:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reparti2
TEMPLATE = app


SOURCES += main.cpp\
    Mainwindow.cpp \
    User.cpp \
    UsersManagerDialog.cpp \
    UserContainer.cpp \
    delete.cpp \
    PayerObserver.cpp \
    Persistence/HtmlExporter.cpp \
    Persistence/UserDbInterface.cpp \
    Persistence/HistoryElement.cpp \
    CustomWidget/PayerWidget.cpp \
    CustomWidget/HistoryWidget.cpp \
    CustomWidget/PayersSelection.cpp \
    CustomWidget/SpaceLineEdit.cpp \
    CustomWidget/PredictionLineEdit.cpp \
    Ticket.cpp

HEADERS  += Mainwindow.h \
    User.hpp \
    UsersManagerDialog.hpp \
    UserContainer.hpp \
    delete.hpp \
    PayerObserver.hpp \
    Persistence/HtmlExporter.hpp \
    Persistence/UserDbInterface.hpp \
    Persistence/HistoryElement.hpp \
    CustomWidget/PayerWidget.hpp \
    CustomWidget/HistoryWidget.hpp \
    CustomWidget/PayersSelection.hpp \
    CustomWidget/SpaceLineEdit.hpp \
    CustomWidget/PredictionLineEdit.hpp \
    Ticket.hpp

FORMS    += mainwindow.ui \
    UsersManager.ui \
    payersselector.ui

CONFIG += c++11

RC_FILE = resource.rc

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    resource.rc
