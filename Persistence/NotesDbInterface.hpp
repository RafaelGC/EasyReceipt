#ifndef NOTESDBINTERFACE_HPP
#define NOTESDBINTERFACE_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlError>
#include <QDebug>

#include "NoteData.hpp"
#include "Config.hpp"

class NotesDbInterface
{
private:
    QSqlDatabase db;
public:
    enum {ORDER_BY_NAME, ORDER_BY_DATE};

    NotesDbInterface();

    bool connect();
    void close();

    std::vector<NoteData> getNotesInfo(int orderBy=ORDER_BY_DATE, bool desc = false) const;
    void getNote(NoteData *data) const;
    QString getNoteString(int id) const;
    NoteData getNote(int id) const;

    bool updateNote(int id, QString note);
    int newNote(QString name, bool *ok);
    bool deleteNote(int id);
};

#endif // NOTESDBINTERFACE_HPP
