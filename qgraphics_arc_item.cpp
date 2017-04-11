#include "qgraphics_arc_item.hpp"
#include <QDebug>
#include <math.h>
QGraphicsArcItem::QGraphicsArcItem(double x1, double y1, double x2, double y2, double angle, QGraphicsItem *parent):QGraphicsEllipseItem(parent)
{
    int r = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    
    _x = x1-r;
    _y = y1-r;
    _x1 =x1;
    _x2 = x2;
    _y1 = y1;
    _y2 = y2;
    _angle =(angle*180/(M_PI))*16;
    _r = r;
    this->setRect(_x,_y,2*r,2*r);
}



void QGraphicsArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{   qDebug()<<"x1 == >"<<_x1;
    qDebug()<<"y1 == >"<<_y1;
    qDebug()<<"x2 == >"<<_x2;
    qDebug()<<"y2 == >"<<_y2;
    qDebug()<<"_x == >"<<_x;
    qDebug()<<"_y == >"<<_y;
    
    qDebug()<<"_r == >"<<_r;
    
    qDebug()<<"_angle == >"<<_angle;
    qDebug()<<(atan2(_y2-_y1,_x1-_x2) *180/M_PI)*16;
    painter->setBrush(Qt::SolidPattern);
    painter->setPen(QPen(Qt::black));
    painter->drawArc(_x,_y,2*_r,2*_r,int((atan2(_y1-_y2,_x2-_x1) *180/M_PI)*16),_angle);
}

