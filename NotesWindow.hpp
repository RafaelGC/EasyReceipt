#ifndef NOTESWINDOW_HPP
#define NOTESWINDOW_HPP

#include <QMainWindow>
#include <QListWidgetItem>
#include <QLocale>
#include <QDebug>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QInputDialog>

#include "CustomWidget/SmallButton.hpp"
#include "Persistence/NotesDbInterface.hpp"
#include "NoteData.hpp"

#include "ui_noteswindow.h"

class NotesWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::NotesWindow *ui;
    SmallButton *orderByName, *orderByDate, *desc;
    NotesDbInterface notesDb;
    bool modified;
    QListWidget *notesList;
    QMenu *contextMenu;


    int currentNoteId;

    void cleanList();
    void makeList();
    void constructList();
    void askForSave();

public:
    explicit NotesWindow(QWidget *parent = 0);
    ~NotesWindow();
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *, QEvent *);

public slots:
    void show();

private slots:
    void orderByNameClicked();
    void orderByDateClicked();
    void orderDesc();

    void selectionChanged();
    void currentItemChanged(QListWidgetItem*current, QListWidgetItem* previous);

    void save();
    void textModified();
    void deleteSelectedNote();

    void newNote();

    void setModified(bool modified);
    void cleanAndBlockEdition(bool state);

};

#endif // NOTESWINDOW_HPP
