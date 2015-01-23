#ifndef NOTESWINDOW_HPP
#define NOTESWINDOW_HPP

#include <QMainWindow>

#include "CustomWidget/SmallButton.hpp"

#include "ui_noteswindow.h"

class NotesWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::NotesWindow *ui;
    SmallButton *orderByName, *orderByDate;
public:
    explicit NotesWindow(QWidget *parent = 0);
    ~NotesWindow();
signals:

public slots:
    void orderByNameClicked();
    void orderByDateClicked();

};

#endif // NOTESWINDOW_HPP
