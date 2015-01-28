#ifndef NOTEDATA_HPP
#define NOTEDATA_HPP

#include <QString>
#include <QDate>

class NoteData
{
protected:
    bool noteLoaded;
    QString name, note;
    QDate date;
    int id;
public:
    NoteData();
    NoteData(int id, QString name, QString date);

    bool isLoaded() const;

    QString getName() const;
    QString getNote() const;
    QDate getDate() const;
    QString getDateString() const;
    int getId() const;

    void setName(const QString &name);
    void setDate(const QDate &date);
    void setId(int id);
    void setNote(const QString &note);

};

#endif // NOTEDATA_HPP
