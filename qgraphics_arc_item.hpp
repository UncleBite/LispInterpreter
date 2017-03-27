#ifndef QGRAPHICS_ARC_ITEM_HPP
#define QGRAPHICS_ARC_ITEM_HPP

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsEllipseItem>

class QGraphicsArcItem : public QGraphicsEllipseItem
{
public:
    QGraphicsArcItem(QGraphicsItem *parent = Q_NULLPTR);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void setArguments(double x, double y, double width, double height, double angle);

private:
    int _x;
    int _y;
    int _d;
    int _start;
    int _angle;
};

#endif // QGRAPHICS_ARC_ITEM_HPP
