#include "canvas_widget.hpp"
#include "qgraphics_arc_item.hpp"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    scene->setSceneRect(-400, -300,800, 600);


    //QGraphicsArcItem* arc = new QGraphicsArcItem;
    //this->addGraphic(arc);
}

void CanvasWidget::addGraphic(QGraphicsItem* item)
{
    scene->addItem(item);
    //qDebug()<<scene->items().size();
}

QSize CanvasWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize CanvasWidget::sizeHint() const
{
    return QSize(800, 600);
}

