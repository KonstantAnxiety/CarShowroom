#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include "vector.h"
#include "podium.h"
#include "carshowroom.h"
#include "auxiliary.h"

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicView(QWidget *parent, double sceneWidth = 100,
                  double sceneHeight = 100);
    ~MyGraphicView();
    void addItems(const CarShowroom &items);
    void addLine(double x1, double y1, double x2, double y2,
                 const QPen &pen = QPen(Qt::black));
    void addCircle(double x, double y, double r,
                   const QPen &pen = QPen(Qt::black));
    void addLabel(const QString &str, double x, double y,
                  const QColor &color = Qt::black, double scale = .2,
                  int align = -1, int valign = -1);
                  // -1:0:1 = left:center:right = top:middle:bottom

private:
    QGraphicsScene      *scene;
    QGraphicsItemGroup  *circles;    // podiums
    QGraphicsItemGroup  *rectangles; // cars
    QGraphicsItemGroup  *group_1;    // grid and border
    Vector<std::shared_ptr<QGraphicsItem>> labels;

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

    bool _pan;
    int _panStartX, _panStartY;

    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);
};

#endif // MYGRAPHICVIEW_H
