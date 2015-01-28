#include "NotesDbInterface.hpp"

NotesDbInterface::NotesDbInterface()
{
    db = QSqlDatabase::addDatabase("QSQLITE","NOTES");
    db.setDatabaseName("notes.db");
}

bool NotesDbInterface::connect()
{
    if (!db.open()){
        return false;
    }

    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS notes(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, date TEXT, note TEXT)")){
        qDebug() << query.lastError().text();
    }

    return true;
}

void NotesDbInterface::close()
{
    db.close();
}

std::vector<NoteData> NotesDbInterface::getNotesInfo(int orderBy, bool desc) const
{
    std::vector<NoteData> notes;

    QString orderConfig = "order by ";
    if (orderBy==ORDER_BY_NAME){
        orderConfig.append("name");
    }
    else if (orderBy==ORDER_BY_DATE){
        orderConfig.append("date");
    }
    if (desc){
        orderConfig.append(" DESC");
    }


    QSqlQuery query(db);
    query.exec(QString("SELECT id, name, date FROM notes ").append(orderConfig));

    QSqlRecord record = query.record();
    int idCol = record.indexOf("id");
    int nameCol = record.indexOf("name");
    int dateCol = record.indexOf("date");
    while (query.next()){

        NoteData note(query.value(idCol).toInt(),
                      query.value(nameCol).toString()
                      ,query.value(dateCol).toString());
        notes.push_back(note);
    }

    return notes;
}

void NotesDbInterface::getNote(NoteData *data) const
{
    QSqlQuery query(db);
    if (query.exec(QString("SELECT note from notes where id=%1 limit 1").arg(data->getId()))){
        QSqlRecord record = query.record();
        int noteCol = record.indexOf("note");
        if (query.next()){
            data->setNote(query.value(noteCol).toString());
        }
    }
}

QString NotesDbInterface::getNoteString(int id) const
{
    QSqlQuery query(db);
    if (query.exec(QString("SELECT note from notes where id=%1 limit 1").arg(id))){
        if (query.next()){
            return query.value(0).toString();
        }
    }
    return QString();
}

NoteData NotesDbInterface::getNote(int id) const
{
    QSqlQuery query(db);
    if (query.exec(QString("SELECT id, name, date, note from notes where id=%1 limit 1").arg(id))){
        QSqlRecord record = query.record();
        int idCol = record.indexOf("id");
        int nameCol = record.indexOf("name");
        int dateCol = record.indexOf("date");
        int noteCol = record.indexOf("note");
        if (query.next()){

            NoteData note(query.value(idCol).toInt(),
                          query.value(nameCol).toString()
                          ,query.value(dateCol).toString());
            note.setNote(query.value(noteCol).toString());
            return note;
        }
    }
    return NoteData();
}

bool NotesDbInterface::updateNote(int id, QString note)
{
    QSqlQuery query(db);
    if (query.exec(QString("update notes set note='%1' where id=%2").arg(note).arg(id))){
        return true;
    }
    return false;
}

int NotesDbInterface::newNote(QString name, bool *ok)
{
    QSqlQuery query(db);

    (*ok) = (query.exec(QString("insert into notes values(NULL,'%1','%2','')")
                   .arg(name)
                   .arg(QDate::currentDate().toString("yyyy-MM-dd"))));
    return query.lastInsertId().toInt();
}

bool NotesDbInterface::deleteNote(int id)
{
    QSqlQuery query(db);

    return query.exec(QString("delete from notes where id=%1").arg(id));
}


