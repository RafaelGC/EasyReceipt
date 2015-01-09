#include "SpaceLineEdit.hpp"

SpaceLineEdit::SpaceLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void SpaceLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->text()=="." && (event->modifiers()&Qt::KeypadModifier)){
        this->setText(this->text().insert(this->cursorPosition(),QLocale::system().decimalPoint()));
    }
    else if (event->key()==Qt::Key::Key_Space){
        emit this->spacePressed();
        return;
    }

    QLineEdit::keyPressEvent(event);
}
