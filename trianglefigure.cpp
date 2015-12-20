#include "trianglefigure.h"

TriangleFigure::TriangleFigure()
{
    maxCoord = 0;
    maxBrightness = 0;
}

TriangleFigure::TriangleFigure(TriangleFigure &tf)
{
    this->triangles = tf.triangles;
    this->maxBrightness = tf.maxBrightness;
    this->maxCoord = tf.maxCoord;
}

int TriangleFigure::getPlaneSide(Triangle *triangle)
{
    //нормаль к OXY Nx = 0; Ny = 0;
    double Nz = -10;
    double cosA = (triangle->getNormal(2) * Nz);// / (norma * 10.0);
    if (fabs(cosA) < 0.00000001) {/*qDebug() << "null";*/ return 1;}
    if (cosA < 0)
    {
        return 2;
    } else
    {
        return 1;
    }
}

void TriangleFigure::addTriangle(Triangle *tr)
{
    Triangle *newTriangle = new Triangle(*tr);
    //qDebug() << "triangle added " << newTriangle->getBrightness();
    if (newTriangle->getXmax() > maxCoord) {maxCoord = newTriangle->getXmax();}
    if (newTriangle->getYmax() > maxCoord) {maxCoord = newTriangle->getYmax();}
    if (newTriangle->getZmax() > maxCoord) {maxCoord = newTriangle->getZmax();}
    if (newTriangle->getBrightness() > maxBrightness) {maxBrightness = newTriangle->getBrightness();}
    //qDebug() << "maxBrightness = " << maxBrightness;
    this->triangles.append(newTriangle);
}

void TriangleFigure::turn(char axis, double angle)
{
    for (int i = 0; i < triangles.size(); i++)
    {
        Figure triangle;
        Triangle *currentTr = triangles[i];
        triangle.addPoint(currentTr->getCoord(0,0), currentTr->getCoord(0,1), currentTr->getCoord(0,2));
        triangle.addPoint(currentTr->getCoord(1,0), currentTr->getCoord(1,1), currentTr->getCoord(1,2));
        triangle.addPoint(currentTr->getCoord(2,0), currentTr->getCoord(2,1), currentTr->getCoord(2,2));
        triangle.turn(axis, angle);
        for (int j = 0; j < 3; j++)
        {
            currentTr->editPoint(j, triangle.getCoord(j,0), triangle.getCoord(j,1), triangle.getCoord(j,2));
        }
    }

}

void TriangleFigure::draw(QPaintDevice *device)
{
    QPainter painter(device);
    QPen pen;
    int QWHeight = device->height();
    int QWWidth = device->width();
    int CentX = QWWidth/2;
    int CentY = QWHeight/2;
    double scale = (maxCoord / std::min(QWHeight,QWWidth))*2;

    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.drawLine(0,CentY,QWWidth,CentY);
    painter.drawLine(CentX,0,CentX,QWHeight);
    qDebug() << "triangles to draw: " << triangles.size() << " max absolute brightness = " << maxBrightness;
    for (int i = 0; i < triangles.size(); i++)
    {
        Triangle *currentTr = triangles[i];
        if (getPlaneSide(currentTr) == 1)
        {
            QColor color;
            color.setRgbF(0, 0, currentTr->getBrightness()/(maxBrightness+15.0));
            pen.setColor(color);
            painter.setPen(pen);
            painter.setBrush(color);
        } else
        {
            QColor color;
            color.setRgbF(currentTr->getBrightness()/(maxBrightness+15.0), 0, 0);
            pen.setColor(color);
            painter.setPen(pen);
            painter.setBrush(color);
        }
        const QPointF points[3] = {
            QPointF(currentTr->getCoord(0,0)/scale+CentX, QWHeight - currentTr->getCoord(0,1)/scale+1-CentY),
            QPointF(currentTr->getCoord(1,0)/scale+CentX, QWHeight - currentTr->getCoord(1,1)/scale+1-CentY),
            QPointF(currentTr->getCoord(2,0)/scale+CentX, QWHeight - currentTr->getCoord(2,1)/scale+1-CentY)
        };
       painter.drawPolygon(points, 3, Qt::WindingFill);
    }
}

TriangleFigure::~TriangleFigure()
{
    int trSize = triangles.size();
    for (int i = 0; i < trSize; i++)
    {
        delete triangles[0];
        triangles.removeFirst();
    }
}

