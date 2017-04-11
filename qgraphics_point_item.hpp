#ifndef QGRAPHICS_POINT_ITEM_HPP
#define QGRAPHICS_POINT_ITEM_HPP


#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QRectF>
#include <QPainterPath>
class QGraphicsPointItem : public QGraphicsEllipseItem
{
public:
    QGraphicsPointItem(qreal x, qreal y);
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape()const;
private:
    double _x;
    double _y;
};

#endif // QGRAPHICS_POINT_ITEM_HPP
