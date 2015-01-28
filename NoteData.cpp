#include "NoteData.hpp"

NoteData::NoteData()
{
    id = -1;
    noteLoaded = false;
}

NoteData::NoteData(int id, QString name, QString date)
{
    this->id = id;
    this->name = name;
    this->date = QDate::fromString(date,"yyyy-MM-dd");
    noteLoaded = false;
}

bool NoteData::isLoaded() const
{
    return noteLoaded;
}

QString NoteData::getName() const
{
    return name;
}

QString NoteData::getNote() const
{
    return note;
}

QDate NoteData::getDate() const
{
    return date;
}

QString NoteData::getDateString() const
{
    return date.toString("yyyy-MM-dd");
}

int NoteData::getId() const
{
    return id;
}

void NoteData::setName(const QString &name)
{
    this->name = name;
}

void NoteData::setDate(const QDate &date)
{
    this->date = date;
}

void NoteData::setId(int id)
{
    this->id = id;
}

void NoteData::setNote(const QString &note)
{
    this->note = note;
}
