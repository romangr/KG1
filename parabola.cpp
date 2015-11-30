#include "parabola.h"

Parabola::Parabola(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    points = new Matrix();
    //points = new Matrix();
    points->addLine(x1, y1, z1, 0);
    points->addLine(x2, y2, z2, 0);
    points->addLine(x3, y3, z3, 0);
    //x
    Ax0 = points->getElement(0, 0);
    Ax2 = 2.0*(points->getElement(2, 0) - 2.0*points->getElement(1, 0) + points->getElement(0, 0));
    Ax1 = points->getElement(2, 0) - points->getElement(0, 0) - Ax2;
    //y
    Ay0 = points->getElement(0, 1);
    Ay2 = 2.0*(points->getElement(2, 1) - 2.0*points->getElement(1, 1) + points->getElement(0, 1));
    Ay1 = points->getElement(2, 1) - points->getElement(0, 1) - Ay2;
    //z
    Az0 = points->getElement(0, 2);
    Az2 = 2.0*(points->getElement(2, 2) - 2.0*points->getElement(1, 2) + points->getElement(0, 2));
    Az1 = points->getElement(2, 2) - points->getElement(0, 2) - Az2;
}

Parabola::Parabola(Parabola &p)
{
    points = new Matrix();
    *this->points = *p.points;
    this->Ax0 = p.Ax0;
    this->Ax2 = p.Ax2;
    this->Ax1 = p.Ax1;
    this->Ay0 = p.Ay0;
    this->Ay2 = p.Ay2;
    this->Ay1 = p.Ay1;
    this->Az0 = p.Az0;
    this->Az2 = p.Az2;
    this->Az1 = p.Az1;
}

double Parabola::getX(double t)
{
    return Ax0 + Ax1*t + Ax2*t*t;
}

double Parabola::getY(double t)
{
    return Ay0 + Ay1*t + Ay2*t*t;
}

double Parabola::getZ(double t)
{
    return Az0 + Az1*t + Az2*t*t;
}

double *Parabola::getPoint(double t)
{
    double *point = new double[4];
    point[0] = getX(t);
    point[1] = getY(t);
    point[2] = getZ(t);
    point[3] = 0;
    return point;
}

Parabola::~Parabola()
{
    delete(points);
}

