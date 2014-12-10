#include "PredictionLineEdit.hpp"

PredictionLineEdit::PredictionLineEdit(UserContainer *userContainer, QWidget *parent) :
    QLineEdit(parent)
{
    this->userContainer = userContainer;
}

void PredictionLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (this->cursorPosition()!=this->text().size()){
        QLineEdit::keyPressEvent(event);
        return;
    }

    if (event->key()==Qt::Key::Key_Backspace || event->key()==Qt::Key::Key_Delete ){
        QLineEdit::keyPressEvent(event);
        return;
    }

    if (event->key()!=Qt::Key::Key_Comma){
        QLineEdit::keyPressEvent(event);
    }

    int startIndex = this->text().lastIndexOf(',',this->cursorPosition()-2);

    if (startIndex<0){
        startIndex = 0;
    }
    else{
        startIndex++;
    }

    QString token = this->text().mid(startIndex,cursorPosition()-startIndex).trimmed();
    if (!token.isEmpty()){
        User* user = userContainer->getUserNameStartWith(token);
        if (user){
            QString finalText = this->text().replace(startIndex,cursorPosition()-startIndex,user->getName()+",");
            this->setText(finalText);
        }
    }

    if (event->key()==Qt::Key::Key_Comma){
        QLineEdit::keyPressEvent(event);
    }


}
