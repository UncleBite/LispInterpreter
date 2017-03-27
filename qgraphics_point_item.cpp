#include "qgraphics_point_item.hpp"

QGraphicsPointItem::QGraphicsPointItem(qreal x,qreal y)  {
    _x = round(x);
    _y = round(y);
}

QRectF QGraphicsPointItem::boundingRect()const{
    return QRectF(1, 1, 1, 1);
}

QPainterPath QGraphicsPointItem::shape()const{
    QPainterPath path;
    path.addRect(QRectF(1, 1, 1, 1));
    return path;
}

void QGraphicsPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPoint(_x, _y);
}
