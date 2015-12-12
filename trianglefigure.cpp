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

    for (int i = 0; i < triangles.size(); i++)
    {
        Triangle *currentTr = triangles[i];
        if (getPlaneSide(currentTr) == 1)
        {
            pen.setColor(Qt::blue);
            painter.setPen(pen);
            painter.setBrush(Qt::blue);
        } else
        {
            pen.setColor(Qt::red);
            painter.setPen(pen);
            painter.setBrush(Qt::red);
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

