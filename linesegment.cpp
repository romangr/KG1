#include "linesegment.h"
#include <qdebug.h>

LineSegment::LineSegment(Matrix &m)
{
    this->coords = m;
    this->coords.addLine(m.getElement(1,0)-m.getElement(0,0), m.getElement(1,1)-m.getElement(0,1), m.getElement(1,2)-m.getElement(0,2), 0);
    this->intersections = new Matrix();
    this->intersections->addLine(0, 1, 0, 0);
}

LineSegment::LineSegment(double x1, double y1, double z1, double x2, double y2, double z2)
{
    this->coords.addLine(x1, y1, z1, 0);
    this->coords.addLine(x2, y2, z2, 0);
    this->coords.addLine(x2-x1, y2-y1, z2-z1, 0);
    this->intersections = new Matrix();
    this->intersections->addLine(0, 1, 0, 0);
}

double LineSegment::getX(double t)
{
    return this->coords.getElement(0,0) + this->coords.getElement(2,0)*t;
}

double LineSegment::getY(double t)
{
    return this->coords.getElement(0,1) + this->coords.getElement(2,1)*t;
}

double LineSegment::getZ(double t)
{
    return this->coords.getElement(0,2) + this->coords.getElement(2,2)*t;
}

double *LineSegment::getPoint(double t)
{
    double *point = new double[4];
    point[0] = getX(t);
    point[1] = getY(t);
    point[2] = getZ(t);
    point[3] = 0;
    return point;

}

double LineSegment::getCoord(int x, int y)
{
    this->coords.getElement(x, y);
}

double LineSegment::getTbyX(double x)
{
    return (x - coords.getElement(0,0)) / coords.getElement(2,0);
}

void LineSegment::addIntersection(double t1, double t2)
{
    this->intersections->addLine(t1, t2, 0, 0);
}

double *LineSegment::calculateIntersections()
{
    while (this->intersections->getHeight() > 1)
    {
        double t1b = this->intersections->getElement(0,0);
        double t1e = this->intersections->getElement(0,1);
        double t2b = this->intersections->getElement(1,0);
        double t2e = this->intersections->getElement(1,1);
        if (t1b > t2b) {
            double buf = t1b;
            double buf2 = t1e;
            t1b = t2b;
            t1e = t2e;
            t2b = buf;
            t2e = buf2;
        }
        if (t1e < t2b) {return NULL;}
        if (t2e > t1e)
        {
            /*double newTb = t2b;
            double newTe = t1e;*/
            //qDebug() << "t2e > t1e";
            this->intersections->deleteLine(0);
            this->intersections->setElement(0,0,t2b);
            this->intersections->setElement(0,1,t1e);
        } else
        {
            //qDebug() << "!(t2e > t1e)";
            this->intersections->deleteLine(0);
            this->intersections->setElement(0,0,t2b);
            this->intersections->setElement(0,1,t2e);
        }
    }
    double *result = new double[2];
    result[0] = this->intersections->getElement(0,0);
    result[1] = this->intersections->getElement(0,1);
    return result;
}

LineSegment::~LineSegment()
{
    delete(intersections);
}

