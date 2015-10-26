#include "figure.h"
#include <stdlib.h>
#include <math.h>

Figure::Figure()
{
    coords = new Matrix();
    coords_last = new Matrix();
    coords_before_last = new Matrix();
    adjacency = new Matrix();
    frontViewScale = 1;
}

Figure::Figure(Matrix &c)
{
    if(c.getWidth() != 4)
    {
        qDebug() << "Figure matrix must have 4 columns";
        this->coords = new Matrix();
        return;
    }
    this->coords = new Matrix(c);
    coords_before_last = new Matrix();
    adjacency = new Matrix();
    this->adjacency = new Matrix(c.getHeight(), c.getHeight());
    frontViewScale = 1;
}

Matrix Figure::getFrontView(int state)
{
    Matrix frontView;
    switch (state) {
   case 1:
        frontView = *(this->coords_last);
        break;
    case 2:
        frontView = *(this->coords_before_last);
        break;
    default:
        frontView = *(this->coords);
        break;
    }

    Matrix frontViewTransform(4, 4);
    for (int i = 1; i <= 4; i*=2)
    {
        frontViewTransform.setElement(i-1, i-1, 1);
    }

    frontView = frontView * frontViewTransform;
    if (fabs(frontViewScale-1) > 0.00001)
    {
        frontView.mult_scalar(frontViewScale);
    }
    return frontView;
}

void Figure::printMatrix()
{
    this->coords->print();
}

void Figure::printAdjacency()
{
    this->adjacency->print();
}

Figure::~Figure()
{
    delete(coords);
}

void Figure::transform(Matrix &transformMatrix)
{

    delete(this->coords_before_last);
    this->coords_before_last = this->coords_last;
    this->coords_last = this->coords;

    if (transformMatrix.getHeight() != 4 || transformMatrix.getWidth() != 4) {qDebug() << "Transform matrix have to be 4x4"; return;}
    Matrix *newCoords = new Matrix();
    *newCoords = *(this->coords);

    *newCoords = *newCoords*transformMatrix;

    this->coords = newCoords;
}

void Figure::turn(char axis, double angle)
{
    const double EPSILON = 0.000000000001;
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
    }

    this->transform(transformMatrix);
}

void Figure::addPoint(double x, double y, double z)
{
    this->coords->addLine(x, y, z, 0);
    //add to adjacency
    this->adjacency->enlarge();
}

void Figure::editPoint(int point, double x, double y, double z) //number of point from {1, ..., N}
{
        this->coords->setElement(point-1, 0, x);
        this->coords->setElement(point-1, 1, y);
        this->coords->setElement(point-1, 2, z);
}

void Figure::setEdge(int point1, int point2, bool state) //number of point from {1, ..., N}
{
    double element;
    switch(state)
    {
    case true: element = 2; break;
    case false: element = 0; break;
    }

    if (point1 > point2)
    {
        int c = point1;
        point1 = point2;
        point2 = c;
    }

    this->adjacency->setElement(point1-1, point2-1, element);
    this->adjacency->setElement(point2-1, point1-1, element);
}

bool Figure::edgeExist(int point1, int point2) //number of point from {1, ..., N}
{
    if (this->adjacency->getElement(point1, point2)>1)
    {
        return true;
    } else
    {
        return false;
    }
}

void Figure::autoscale(QPaintDevice *device)
{
    int width =  device->width();
    int height = device->height();
    int CentX = width/2;
    int CentY = height/2;

    double x,y,z;
    this->coords->findMaxXYZ(x,y,z);

    double k1 = CentX/x;
    double k2 = CentY/y;

    if (k1<k2)
    {
        frontViewScale = k1;
    }
    else
    {
        frontViewScale = k2;
    }
    //запас 5%
    frontViewScale *= 0.95;
}

void Figure::draw(QPaintDevice *device)
{
    QPainter painter(device);
    QPen pen;
    QColor color;
    Matrix m; //store frontView

    int h = this->adjacency->getHeight();
    int QWHeight = device->height();
    int QWWidth = device->width();
    int CentX = QWWidth/2;
    int CentY = QWHeight/2;

    pen.setColor(Qt::gray);
    painter.setPen(pen);

    painter.drawLine(0,CentY,QWWidth,CentY);
    painter.drawLine(CentX,0,CentX,QWHeight);


    m = this->getFrontView(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    for (int i=0; i<h; i++)
    {
        for (int j=0; j<h; j++)
        {
            //вообще надо бегать выше диагонали, т.к. i^j=j^i, а информацию о связях мы записывали в виде i-j, где i<j
            if (j>i) continue;

            if (this->edgeExist(i,j))
                { painter.drawLine(m.getElement(i,0)+CentX,QWHeight - m.getElement(i,1)+1-CentY,m.getElement(j,0)+CentX,QWHeight - m.getElement(j,1)+1-CentY); }

        }
    }
    m = this->getFrontView(1);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    for (int i=0; i<h; i++)
    {
        for (int j=0; j<h; j++)
        {
            //вообще надо бегать выше диагонали, т.к. i^j=j^i, а информацию о связях мы записывали в виде i-j, где i<j
            if (j>i) continue;

            if (this->edgeExist(i,j))
                { painter.drawLine(m.getElement(i,0)+CentX,QWHeight - m.getElement(i,1)+1-CentY,m.getElement(j,0)+CentX,QWHeight - m.getElement(j,1)+1-CentY); }

        }
    }

    m = this->getFrontView(0);
    pen.setColor(Qt::green);
    painter.setPen(pen);
    for (int i=0; i<h; i++)
    {
        for (int j=0; j<h; j++)
        {
            //вообще надо бегать выше диагонали, т.к. i^j=j^i, а информацию о связях мы записывали в виде i-j, где i<j
            if (j>i) continue;

            if (this->edgeExist(i,j))
                { painter.drawLine(m.getElement(i,0)+CentX,QWHeight - m.getElement(i,1)+1-CentY,m.getElement(j,0)+CentX,QWHeight - m.getElement(j,1)+1-CentY); }

        }
    }
}

void Figure::resetLastCoord()
{
    *this->coords_before_last = *coords;
    *this->coords_last = *coords;
}
