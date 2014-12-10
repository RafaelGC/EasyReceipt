#ifndef CUSTOMLINEEDIT_HPP
#define CUSTOMLINEEDIT_HPP

#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

#include "UserContainer.hpp"

class PredictionLineEdit : public QLineEdit
{
    Q_OBJECT
private:
    UserContainer *userContainer;
    void keyPressEvent(QKeyEvent *);

public:
    explicit PredictionLineEdit(UserContainer * userContainer,QWidget *parent = 0);
    //void provideUserContainer(const UserContainer & userContainer);
signals:

public slots:

};

#endif // CUSTOMLINEEDIT_HPP
