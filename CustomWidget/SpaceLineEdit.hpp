#ifndef SPACELINEEDIT_HPP
#define SPACELINEEDIT_HPP

#include <QLineEdit>
#include <QKeyEvent>

#include <QDebug>

class SpaceLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SpaceLineEdit(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *);
signals:
    void spacePressed();
public slots:

};

#endif // SPACELINEEDIT_HPP
