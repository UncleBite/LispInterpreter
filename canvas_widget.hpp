#ifndef CANVAS_WIDGET_HPP
#define CANVAS_WIDGET_HPP

#include <tuple>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGridLayout>
#include <QDebug>


class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    // Default construct a CanvasWidget
    CanvasWidget(QWidget * parent = nullptr);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void line(std::tuple<double, double> start, std::tuple<double, double> end);
    void arc(std::tuple<double, double> start, std::tuple<double, double> end, double degree);

    QGraphicsScene* scene;
    QGraphicsView* view;

    friend class QtInterpreter;



signals:

public slots:
    // A public slot that accepts a signal in the form of a QGraphicItem pointer containing an
    // object derived from QGraphicsItem to draw
    void addGraphic(QGraphicsItem* item);
};

#endif // CANVAS_WIDGET_HPP
