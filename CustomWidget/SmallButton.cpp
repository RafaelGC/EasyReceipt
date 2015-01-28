#include "SmallButton.hpp"

SmallButton::SmallButton(QWidget *parent) :
    QAbstractButton(parent){
    setColors(QColor(200,200,200));
    this->setCursor(Qt::PointingHandCursor);
}

void SmallButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (this->isChecked() || this->isDown()){
        p.fillRect(0,0,this->width(),this->height(),backgroundColor);
        p.setPen(Qt::black);
        p.drawLine(0,height()-1,width(),height()-1);
    }
    else{
        //p.fillRect(0,0,this->width(),this->height(),backgroundColor.lighter(120));
    }
    p.setPen(Qt::black);
    p.drawText(0,0,width(),height(),Qt::AlignCenter,text());
}

QSize SmallButton::sizeHint() const
{
    return QSize(fontMetrics().width(text())+2,fontMetrics().height()+2);
}

void SmallButton::setText(const QString &text)
{
    this->setMinimumWidth(fontMetrics().width(text)+2);
    QAbstractButton::setText(text);
}

void SmallButton::setColors(const QColor &backgroundColor)
{
    this->backgroundColor = backgroundColor;
}
