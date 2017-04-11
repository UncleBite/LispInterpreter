#include "canvas_widget.hpp"
#include "qgraphics_arc_item.hpp"
#include <QDebug>
CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene(this);
    //scene->setSceneRect(-400, -300,800, 600);
    view = new QGraphicsView(scene,this);
    //    scene->addEllipse(
    auto canvas_layout= new QVBoxLayout;
    canvas_layout->addWidget(view);
    setLayout(canvas_layout);
}

void CanvasWidget::addGraphic(QGraphicsItem* item)
{
    scene->addItem(item);
    scene->update();
}

QSize CanvasWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize CanvasWidget::sizeHint() const
{
    return QSize(800, 600);
}

