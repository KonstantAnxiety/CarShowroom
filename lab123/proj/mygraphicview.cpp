#include <QMouseEvent>
#include <QScrollBar>
#include <QDebug>
#include "mygraphicview.h"

MyGraphicView::MyGraphicView(QWidget *parent, double sceneWidth, double sceneHeight)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setMinimumHeight(100);
    this->setMinimumWidth(300);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, sceneWidth, -sceneHeight);
    this->setScene(scene);

    group_1 = new QGraphicsItemGroup();
    rectangles = new QGraphicsItemGroup();
    circles = new QGraphicsItemGroup();

    scene->addItem(group_1);            // Add the first group into the scene
    scene->addItem(rectangles);
    scene->addItem(circles);
}

MyGraphicView::~MyGraphicView()
{

}

void MyGraphicView::addItems(const CarShowroom &items)
{
    deleteItemsFromGroup(rectangles);
    deleteItemsFromGroup(circles);
    deleteItemsFromGroup(group_1);
    for (size_t i = 0; i < labels.getSize(); ++i)
        scene->removeItem(labels.at(i).get());
    labels.clear();
    int mg = 20;
    scene->setSceneRect(-mg, mg, items.getLength()+mg, -items.getWidth()-mg);
    for (int x = 0; x <= items.getLength(); x += 10) {
        addLabel(QString::number(x), x, -1, Qt::black, .4, 0, -1);
    }
    for (int y = 0; y <= items.getWidth(); y += 10) {
        addLabel(QString::number(y), -1, y, Qt::black, .4, 1, 0);
    }
    QPen penGray(Qt::gray);
    for (int x = 0; x < items.getLength(); x += 10) {
        for (int y = 0; y < items.getWidth(); y += 10) {
            addLine(x, 0, x, items.getWidth(), penGray);
            addLine(0, y, items.getLength(), y, penGray);
        }
    }
    QPen penBorder(Qt::black);
    penBorder.setWidth(3);
    double w = items.getLength();
    double h = items.getWidth();
    group_1->addToGroup(scene->addLine(0, 0, w, 0, penBorder));
    group_1->addToGroup(scene->addLine(0, 0, 0, -h, penBorder));
    group_1->addToGroup(scene->addLine(w, 0, w, -h, penBorder));
    group_1->addToGroup(scene->addLine(0, -h, w, -h, penBorder));
    for (size_t i = 0; i < items.objects.getSize(); ++i) {
        Car *curCar = dynamic_cast<Car*>(items.objects[i].get());
        if (curCar) {
            Point rect[4];
            getRectCoordinates(*curCar, rect);
            addLine(rect[0].getX(), rect[0].getY(), rect[1].getX(), rect[1].getY());
            addLine(rect[1].getX(), rect[1].getY(), rect[2].getX(), rect[2].getY());
            addLine(rect[2].getX(), rect[2].getY(), rect[3].getX(), rect[3].getY());
            addLine(rect[3].getX(), rect[3].getY(), rect[0].getX(), rect[0].getY());
            addLabel(QString::number(i),
                     curCar->getX()-2,
                     curCar->getY(),
                     Qt::red);
            continue;
        }
        Podium *curPodium = dynamic_cast<Podium*>(items.objects[i].get());
        if (curPodium) {
            addCircle(curPodium->getX(),
                      curPodium->getY(),
                      curPodium->getRadius());
            addLabel(QString::number(i),
                     curPodium->getX()+2,
                     curPodium->getY(),
                     Qt::blue);
        }
    }
    group_1->setZValue(3);
    rectangles->setZValue(2);
    circles->setZValue(2);

}

void MyGraphicView::addLine(double x1, double y1, double x2, double y2, const QPen &pen)
{
    rectangles->addToGroup(scene->addLine(x1, -y1, x2, -y2, pen));
}

void MyGraphicView::addCircle(double x, double y, double r, const QPen &pen)
{
    circles->addToGroup(scene->addEllipse(x-r, -y-r, r*2, r*2, pen));
}

void MyGraphicView::addLabel(const QString &str, double x, double y, const QColor &color, double scale, int align, int valign)
{
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setScale(scale);
    io->setPlainText(str);
    if (align > 0)
        x -= io->boundingRect().width()*scale;
    else if (align == 0)
        x -= io->boundingRect().width()*scale/2;
    if (valign > 0)
        y += io->boundingRect().height()*scale;
    else if (valign == 0)
        y += io->boundingRect().height()*scale/2;
    io->setPos(x, -y);
    io->setDefaultTextColor(color);
    io->setZValue(4);
    scene->addItem(io);
    labels.push_back(std::shared_ptr<QGraphicsItem>(io));
}

void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton)
    {
        _pan = true;
        _panStartX = event->x();
        _panStartY = event->y();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    event->ignore();
}

void MyGraphicView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton)
    {
        _pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    event->ignore();
}

void MyGraphicView::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0)
      scale(1.25, 1.25);
    else
      scale(0.8, 0.8);
}

void MyGraphicView::mouseMoveEvent(QMouseEvent *event)
{
    if (_pan)
    {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - _panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - _panStartY));
        _panStartX = event->x();
        _panStartY = event->y();
        event->accept();
        return;
    }
    event->ignore();

}

/* Method for removing all the elements from the group
 * */
void MyGraphicView::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    /* Loop through all the elements of the scene,
     * and if they belong to the group, passed into the method, then delete them
     * */
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}
