#include "trianglefigure.h"

TriangleFigure::TriangleFigure()
{
    maxCoord = 0;
}

int TriangleFigure::getPlaneSide(Triangle *triangle)
{
    //нормаль к OXY Nx = 0; Ny = 0;
    double Nz = -10;
    /*double norma = sqrt(triangle->getNormal(0)*triangle->getNormal(0) + triangle->getNormal(1)*triangle->getNormal(1)+
                        triangle->getNormal(2)*triangle->getNormal(2));*/
    double cosA = (triangle->getNormal(2) * Nz);// / (norma * 10.0);
    if (fabs(cosA) < 0.00000001) {qDebug() << "null"; return 1;}
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
    if (newTriangle->getXmax() > maxCoord) {maxCoord = newTriangle->getXmax();}
    if (newTriangle->getYmax() > maxCoord) {maxCoord = newTriangle->getYmax();}
    if (newTriangle->getZmax() > maxCoord) {maxCoord = newTriangle->getZmax();}
    this->triangles.append(newTriangle);
}

void TriangleFigure::turn(char axis, double angle)
{
/*    const double EPSILON = 0.000000000001;
    Matrix transformMatrix;
    const double PI = acos(-1);
    angle = angle * PI / 180;
    double sinA = sin(angle);
    double cosA = cos(angle);
    if (fabs(sinA) < EPSILON) sinA = 0;
    if (fabs(cosA) < EPSILON) cosA = 0;

    if (axis == 0) //x
    {
        transformMatrix.addLine(1.0,    0,     0, 0);
        transformMatrix.addLine(0, cosA, -sinA, 0);
        transformMatrix.addLine(0, sinA,  cosA, 0);
        transformMatrix.addLine(0,    0,     0, 1.0);
    }

    if (axis == 1) //y
    {
        transformMatrix.addLine( cosA, 0, sinA, 0);
        transformMatrix.addLine(    0, 1.0,    0, 0);
        transformMatrix.addLine(-sinA, 0, cosA, 0);
        transformMatrix.addLine(    0, 0,    0, 1.0);
    }

    if (axis == 2) //z
    {
        transformMatrix.addLine(cosA, -sinA, 0, 0);
        transformMatrix.addLine(sinA,  cosA, 0, 0);
        transformMatrix.addLine(0,        0, 1.0, 0);
        transformMatrix.addLine(0,        0, 0, 1.0);
    }*/

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
    double scale = (maxCoord / std::min(QWHeight,QWWidth))*1.5;

    pen.setColor(Qt::gray);
    painter.setPen(pen);
    painter.drawLine(0,CentY,QWWidth,CentY);
    painter.drawLine(CentX,0,CentX,QWHeight);
    qDebug() << "triangles to draw: " << triangles.size();
    for (int i = 0; i < triangles.size(); i++)
    {
        Triangle *currentTr = triangles[i];
        if (getPlaneSide(currentTr) == 1)
        {
            QColor color;
            //qDebug() << "/255" << currentTr->getBrightness();///255.0;
            color.setRgbF(0, 0, currentTr->getBrightness()/255.0);
            pen.setColor(color);
            painter.setPen(pen);
            painter.setBrush(color);
        } else
        {
            QColor color;
            color.setRgbF(currentTr->getBrightness()/255.0, 0, 0);
            pen.setColor(color);
            painter.setPen(pen);
            painter.setBrush(color);
        }
        const QPointF points[3] = {
            QPointF(currentTr->getCoord(0,0)/scale+CentX, QWHeight - currentTr->getCoord(0,1)/scale+1-CentY),
            QPointF(currentTr->getCoord(1,0)/scale+CentX, QWHeight - currentTr->getCoord(1,1)/scale+1-CentY),
            QPointF(currentTr->getCoord(2,0)/scale+CentX, QWHeight - currentTr->getCoord(2,1)/scale+1-CentY)
        };
        //painter.drawLine(m.getElement(i,0)+CentX,QWHeight - m.getElement(i,1)+1-CentY,m.getElement(j,0)+CentX,
        //  QWHeight - m.getElement(j,1)+1-CentY);
       painter.drawPolygon(points, 3, Qt::WindingFill);
    }
}

TriangleFigure::~TriangleFigure()
{

}

