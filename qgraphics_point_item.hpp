#ifndef QGRAPHICS_POINT_ITEM_HPP
#define QGRAPHICS_POINT_ITEM_HPP


#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QPainterPath>
class QGraphicsPointItem : public QGraphicsItem
{
public:
    QGraphicsPointItem(qreal x, qreal y);
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape()const;
private:
    int _x;
    int _y;
};

#endif // QGRAPHICS_POINT_ITEM_HPP
