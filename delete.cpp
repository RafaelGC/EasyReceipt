#include "delete.hpp"

Delete::Delete(QWidget *parent) :
    QVBoxLayout(parent)
{
}

Delete::~Delete()
{
    qDebug() << "Deleted";
}
