#include "qgraphics_point_item.hpp"
#include <iostream>
QGraphicsPointItem::QGraphicsPointItem(qreal x,qreal y)  {
    _x = (x);
    _y = (y);
}

QRectF QGraphicsPointItem::boundingRect()const
{
    return QRectF(1, 1, 1, 1);
}

QPainterPath QGraphicsPointItem::shape()const
{
    QPainterPath path;
    path.addRect(QRectF(1, 1, 1, 1));
    return path;
}

void QGraphicsPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->drawPoint(_x, _y);
    painter->setBrush(Qt::black);
    painter->drawEllipse( _x,_y,2.0,2.0);
}
