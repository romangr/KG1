#include "trianglefigure.h"

TriangleFigure::TriangleFigure()
{

}

void TriangleFigure::addTriangle(Triangle *tr)
{
    Triangle *newTriangle = new Triangle(*tr);
    this->triangles.append(newTriangle);
}

void TriangleFigure::draw(QPaintDevice *device)
{
    qDebug() << "paint";
    QPainter painter(device);
    QPen pen;

    int QWHeight = device->height();
    int QWWidth = device->width();
    int CentX = QWWidth/2;
    int CentY = QWHeight/2;

    pen.setColor(Qt::gray);
    painter.setPen(pen);

    painter.drawLine(0,CentY,QWWidth,CentY);
    painter.drawLine(CentX,0,CentX,QWHeight);
    //m = this->getFrontView();
    pen.setColor(Qt::green);
    painter.setPen(pen);
    for (int i = 0; i < triangles.size(); i++)
    {
        Triangle *currentTr = triangles[i];
        const QPointF points[3] = {
            QPointF(currentTr->getCoord(0,0)+CentX, QWHeight - currentTr->getCoord(0,1)+1-CentY),
            QPointF(currentTr->getCoord(1,0)+CentX, QWHeight - currentTr->getCoord(1,1)+1-CentY),
            QPointF(currentTr->getCoord(2,0)+CentX, QWHeight - currentTr->getCoord(2,1)+1-CentY)
        };
        //painter.drawLine(m.getElement(i,0)+CentX,QWHeight - m.getElement(i,1)+1-CentY,m.getElement(j,0)+CentX,
        //  QWHeight - m.getElement(j,1)+1-CentY);
        painter.drawPolygon(points, 3);
    }
}

TriangleFigure::~TriangleFigure()
{

}

