#ifndef SMALLBUTTON_HPP
#define SMALLBUTTON_HPP

#include <QAbstractButton>
#include <QPaintEvent>
#include <QPainter>

class SmallButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit SmallButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    QSize sizeHint() const;
    void setText(const QString &text);
signals:

public slots:

};

#endif // SMALLBUTTON_HPP
