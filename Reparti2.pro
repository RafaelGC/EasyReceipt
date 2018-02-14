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
    User.cpp \
    Dialogs/UsersManagerDialog.cpp \
    UserContainer.cpp \
    PayerObserver.cpp \
    Persistence/UserDbInterface.cpp \
    CustomWidget/PayerWidget.cpp \
    CustomWidget/HistoryWidget.cpp \
    Pages/PayersSelection.cpp \
    CustomWidget/SpaceLineEdit.cpp \
    CustomWidget/PredictionLineEdit.cpp \
    Economy/Ticket.cpp \
    Economy/Product.cpp \
    Economy/TicketContainer.cpp \
    Economy/Debt.cpp \
    Pages/CreateTicketWidget.cpp \
    Pages/ManageTicketWidget.cpp \
    Pages/TotalPayout.cpp \
    Persistence/ConfigDbInterface.cpp \
    Config.cpp \
    Dialogs/AboutDialog.cpp \
    Version.cpp \
    UpdateManager.cpp \
    Dialogs/UpdateDialog.cpp \
    Dialogs/ConfigDialog.cpp \
    NotesWindow.cpp \
    CustomWidget/SmallButton.cpp \
    Persistence/NotesDbInterface.cpp \
    NoteData.cpp \
    Economy/Payers.cpp \
    Economy/UserAmountCollection.cpp \
    Economy/UserAmount.cpp \
    Economy/PaymentDistribution.cpp \
    Economy/MultiTicketDistribution.cpp \
    Persistence/XmlExporter.cpp \
    Persistence/XmlImporter.cpp \
    Persistence/HtmlExporter.cpp \
    HtmlInterface.cpp \
    UserDbLoader.cpp \
    XmlInterface.cpp \
    TicketLoadedListener.cpp \
    MainWindow.cpp

HEADERS  += \
    User.hpp \
    Dialogs/UsersManagerDialog.hpp \
    UserContainer.hpp \
    PayerObserver.hpp \
    Persistence/UserDbInterface.hpp \
    CustomWidget/PayerWidget.hpp \
    CustomWidget/HistoryWidget.hpp \
    Pages/PayersSelection.hpp \
    CustomWidget/SpaceLineEdit.hpp \
    CustomWidget/PredictionLineEdit.hpp \
    Economy/Ticket.hpp \
    Economy/Product.hpp \
    Economy/TicketContainer.hpp \
    Economy/Debt.hpp \
    Pages/CreateTicketWidget.hpp \
    Pages/ManageTicketWidget.hpp \
    Pages/TotalPayout.hpp \
    Persistence/ConfigDbInterface.hpp \
    Config.hpp \
    Dialogs/AboutDialog.hpp \
    Version.hpp \
    UpdateManager.hpp \
    Dialogs/UpdateDialog.hpp \
    Dialogs/ConfigDialog.hpp \
    NotesWindow.hpp \
    CustomWidget/SmallButton.hpp \
    Persistence/NotesDbInterface.hpp \
    NoteData.hpp \
    Economy/Payers.hpp \
    Economy/UserAmountCollection.hpp \
    Economy/UserAmount.hpp \
    Economy/PaymentDistribution.hpp \
    Economy/MultiTicketDistribution.hpp \
    Persistence/XmlExporter.hpp \
    Persistence/XmlImporter.hpp \
    Persistence/HtmlExporter.hpp \
    HtmlInterface.hpp \
    UserDbLoader.hpp \
    XmlInterface.hpp \
    TicketLoadedListener.hpp \
    MainWindow.hpp

FORMS    += mainwindow.ui \
    UsersManager.ui \
    payersselector.ui \
    ticketpanel.ui \
    products.ui \
    finalpayout.ui \
    config.ui \
    aboutform.ui \
    updatedialog.ui \
    noteswindow.ui

CONFIG += c++11
CONFIG += Wall

RC_FILE = resource.rc

RESOURCES += \
    resources.qrc
TRANSLATIONS += text.ts
OTHER_FILES += \
    resource.rc
