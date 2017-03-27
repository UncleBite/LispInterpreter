#include "qgraphics_arc_item.hpp"
#include <QDebug>
#include <math.h>
QGraphicsArcItem::QGraphicsArcItem(QGraphicsItem *parent):QGraphicsEllipseItem(parent)
{
    _x = 0;
    _y = 0;
    _d = 0;
    _start = 0;
    _angle = 0;
}

void QGraphicsArcItem::setArguments(double x1, double y1, double x2, double y2, double angle)
{
    auto r = round(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
    _x = round(x1 - r);
    _y = round(y1 - r);
    _d = 2 * r;
    _angle = round(angle / M_PI * 180 * 16);
    auto c = sqrt((x1 + r - x2)*(x1 + r - x2) + (y1 - y2)*(y1 - y2));
    _start = round(acos((2 * r * r - c * c)/(2 * r * r)) / M_PI * 180 * 16);
}

void QGraphicsArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //painter->drawArc(0.0, 0.0, 10.0, 10.0, 0, 360 * 16);
    qDebug()<<_angle;
    painter->drawArc(_x, _y, _d, _d, _start, _angle);
}

QRectF QGraphicsArcItem::boundingRect()const{
    return QRectF(_x, _y, _d, _d);
}

QPainterPath QGraphicsArcItem::shape()const{
    QPainterPath path;
    path.addRect(QRectF(-_d/2,-_d/2,_d,_d));
    return path;
}
