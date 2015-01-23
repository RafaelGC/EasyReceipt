#include "SmallButton.hpp"

SmallButton::SmallButton(QWidget *parent) :
    QAbstractButton(parent){
}

void SmallButton::paintEvent(QPaintEvent *){
    QPainter p(this);
    if (this->isChecked() || this->isDown()){
        p.fillRect(0,0,this->width(),this->height(),QColor(200,200,200).rgb());
        p.setPen(Qt::red);
        p.drawLine(0,height()-1,width(),height()-1);
    }
    else{
        p.fillRect(0,0,this->width(),this->height(),QColor(220,220,220).rgb());
    }
    p.setPen(Qt::black);
    p.drawText(0,0,width(),height(),Qt::AlignCenter,text());
}

QSize SmallButton::sizeHint() const{
    return QSize(fontMetrics().width(text())+2,fontMetrics().height()+2);
}

void SmallButton::setText(const QString &text){
    this->setMinimumWidth(fontMetrics().width(text)+2);
    QAbstractButton::setText(text);
}
