#include "SpaceLineEdit.hpp"

SpaceLineEdit::SpaceLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void SpaceLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key::Key_Space){
        emit this->spacePressed();
        return;
    }

    QLineEdit::keyPressEvent(event);
}
