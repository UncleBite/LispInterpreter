#ifndef QGRAPHICS_ARC_ITEM_HPP
#define QGRAPHICS_ARC_ITEM_HPP

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsEllipseItem>

class QGraphicsArcItem : public QGraphicsEllipseItem
{
public:
    QGraphicsArcItem(double x1, double y1, double x2, double y2, double angle, QGraphicsItem *parent = Q_NULLPTR);
    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    
    
private:
    int _x;
    int _y;
    double _x1;
    double _y1;
    double _x2;
    double _y2;
    
    double c;
    int _r;
    double w;
    double h;
    int _angle;
};

#endif // QGRAPHICS_ARC_ITEM_HPP
