#include "triangle.h"

Triangle::Triangle(Matrix &m, double a, double b, double c)
{
    this->points = new Matrix(m);
    this->pointNumbers.addLine(a, b, c, 0);
}

bool Triangle::isUnderTriangle(double a, double b, double c)
{
    const double EPSILON = 0.01;
    /*if (!((c < points->getElement(0,2)) && (c < points->getElement(1,2)) && (c < points->getElement(2,2)))) {
        return false;
    }*/
    double s1;
    double s;

    double x1 = points->getElement(0,0); double x2 = points->getElement(1,0); double x3 = points->getElement(2, 0);
    double y1 = points->getElement(0,1); double y2 = points->getElement(1,1); double y3 = points->getElement(2, 1);
    double z1 = points->getElement(0,2); double z2 = points->getElement(1,2); double z3 = points->getElement(2, 2);
    //уравнение плоскости треугольника
    /*A = y1 (z2 - z3) + y2 (z3 - z1) + y3 (z1 - z2)
    B = z1 (x2 - x3) + z2 (x3 - x1) + z3 (x1 - x2)
    C = x1 (y2 - y3) + x2 (y3 - y1) + x3 (y1 - y2)
    - D = x1 (y2 z3 - y3 z2) + x2 (y3 z1 - y1 z3) + x3 (y1 z2 - y2 z1)*/
    double A = y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2);
    double B = z1*(x2 - x3) + z2*(x3 - x1) + z3*(x1 - x2);
    double C = x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2);
    double D = x1*(y2*z3 - y3*z2) + x2*(y3*z1 - y1*z3) + x3*(y1*z2 - y2*z1);
    D = -D;

    s = A*a + B*b + C*c + D;
    if (fabs(s) < EPSILON*0.01) {/*qDebug() << "s < EPSILON*0.01";*/ return false;};
    s1 = C*10000 + D;

    if (s * s1 > 0) {/*qDebug() << "s*s1 > 0";*/ return false;}

    Matrix *vectors = new Matrix();
    vectors->addLine(points->getElement(0,0) - a, points->getElement(0,1) - b, 0/*points->getElement(0,2)*/, 0);
    vectors->addLine(points->getElement(1,0) - a, points->getElement(1,1) - b, 0/*points->getElement(1,2)*/, 0);
    vectors->addLine(points->getElement(2,0) - a, points->getElement(2,1) - b, 0/*points->getElement(2,2)*/, 0);
    vectors->addLine(0, 0, 0, 0);

    for (int i = 0; i < 3; i++)
    {
        double ab = vectors->getElement(i,0) * vectors->getElement(((i+1)%3),0) + vectors->getElement(i,1) * vectors->getElement(((i+1)%3),1) + vectors->getElement(i,2) * vectors->getElement(((i+1)%3),2);
        double modul1 = sqrt(vectors->getElement(i,0)*vectors->getElement(i,0) + vectors->getElement(i,1)*vectors->getElement(i,1) + vectors->getElement(i,2)*vectors->getElement(i,2));
        double modul2 = sqrt(vectors->getElement(((i+1)%3),0)*vectors->getElement(((i+1)%3),0) + vectors->getElement(((i+1)%3),1)*vectors->getElement(((i+1)%3),1) + vectors->getElement(((i+1)%3),2)*vectors->getElement(((i+1)%3),2));
        vectors->setElement(3, i, 57.2958*acos(ab/(modul1*modul2)));
    }
    //qDebug() << vectors->getElement(3, 0) << " " << vectors->getElement(3, 1) << " " << vectors->getElement(3, 2);
    //qDebug() << vectors->getElement(3, 0) + vectors->getElement(3, 1) + vectors->getElement(3, 2);

    if (fabs(( vectors->getElement(3, 0) + vectors->getElement(3, 1) + vectors->getElement(3, 2)) - 360.0) < EPSILON)
    {
        qDebug() << (vectors->getElement(3, 0) + vectors->getElement(3, 1) + vectors->getElement(3, 2));
        //return true;
    }
    else
    {
        return false;
    }
    s = (y1-y2)*a + (x2-x1)*b + (x1*y2 - x2*y1);
    if (fabs(s) < EPSILON) {s = 0;}
    double p = (y1-y2)*x3 + (x2-x1)*y3 + (x1*y2 - x2*y1);

    s1 = (y1-y3)*a + (x3-x1)*b + (x1*y3 - x3*y1);
    if (fabs(s1) < EPSILON) {s1 = 0;}
    double p1 =  (y1-y3)*x2 + (x3-x1)*y2 + (x1*y3 - x3*y1);

    double s2 =  (y2-y3)*a + (x3-x2)*b + (x2*y3 - x3*y2);
    if (fabs(s2) < EPSILON) {s2 = 0;}
    double p2 = (y2-y3)*x1 + (x3-x2)*y1 + (x2*y3 - x3*y2);

    if (s*p > EPSILON*0.01 && s1*p1 > EPSILON*0.01 && s2*p2 > EPSILON*0.01)
    {
       /* qDebug() << " s = " << s << " s1 = " << s1 << " s2 = " << s2;*/
        /*qDebug() << "a = " << a << "b = " << b << "c = " << c;
        qDebug() << "x1 = " << x1 << "y1 = " << y1 << "z1 = " << z1;
        qDebug() << "x2 = " << x2 << "y2 = " << y2 << "z2 = " << z2;
        qDebug() << "x3 = " << x3 << "y3 = " << y3 << "z3 = " << z3;*/
        return true;
    }
    else
    {/*qDebug() << "last false";*/ return false;}
}

bool Triangle::isBehindTriangle(double z)
{
    if (z > this->points->getElement(0,2)) {return false;}
    if (z > this->points->getElement(1,2)) {return false;}
    if (z > this->points->getElement(2,2)) {return false;}
    return true;
}

bool Triangle::isInFrontOfTriangle(double z)
{
    if (z < this->points->getElement(0,2)) {return false;}
    if (z < this->points->getElement(1,2)) {return false;}
    if (z < this->points->getElement(2,2)) {return false;}
    return true;
}

bool Triangle::isInProjection(double a, double b)
{
    double x1 = points->getElement(0,0); double x2 = points->getElement(1,0); double x3 = points->getElement(2, 0);
    double y1 = points->getElement(0,1); double y2 = points->getElement(1,1); double y3 = points->getElement(2, 1);
    //double z1 = points->getElement(0,2); double z2 = points->getElement(1,2); double z3 = points->getElement(2, 2);
    double s, s1;
    double EPSILON = 0.01;
    s = (y1-y2)*a + (x2-x1)*b + (x1*y2 - x2*y1);
    if (fabs(s) < EPSILON) {s = 0;}
    double p = (y1-y2)*x3 + (x2-x1)*y3 + (x1*y2 - x2*y1);

    s1 = (y1-y3)*a + (x3-x1)*b + (x1*y3 - x3*y1);
    if (fabs(s1) < EPSILON) {s1 = 0;}
    double p1 =  (y1-y3)*x2 + (x3-x1)*y2 + (x1*y3 - x3*y1);

    double s2 =  (y2-y3)*a + (x3-x2)*b + (x2*y3 - x3*y2);
    if (fabs(s2) < EPSILON) {s2 = 0;}
    double p2 = (y2-y3)*x1 + (x3-x2)*y1 + (x2*y3 - x3*y2);

    if (s*p > EPSILON*0.01 && s1*p1 > EPSILON*0.01 && s2*p2 > EPSILON*0.01)
    {
        return true;
    }
    return false;
}

bool Triangle::isApex(int pointNumber)
{
    if (pointNumber == pointNumbers.getElement(0,0)) {return true;}
    if (pointNumber == pointNumbers.getElement(0,1)) {return true;}
    if (pointNumber == pointNumbers.getElement(0,2)) {return true;}
    return false;
}

bool Triangle::isEdge(LineSegment *ls)
{
    if (this->isApex(ls->getFigurePoint(0)) && this->isApex(ls->getFigurePoint(1)))
    {
        return true;
    }
    return false;
    //return true;
}

double Triangle::getCoord(int x, int y)
{
    return this->points->getElement(x, y);
}

void Triangle::setNormal(int point1, int point2, int point3, int point4)
{
    if (point1 > 2 || point2 > 2 || point3 > 2 || point4 > 2) {qDebug() << "Points must be from [0,2]"; return;}
    //if (normal != NULL) { delete normal;} проверка не работает!
    this->normal = new double[3];
    double Ax = (points->getElement(point2,0) - points->getElement(point1,0));
    double Ay = (points->getElement(point2,1) - points->getElement(point1,1));
    double Az = (points->getElement(point2,2) - points->getElement(point1,2));
    double Bx = (points->getElement(point4,0) - points->getElement(point3,0));
    double By = (points->getElement(point4,1) - points->getElement(point3,1));
    double Bz = (points->getElement(point4,2) - points->getElement(point3,2));
    this->normal[0] = Ay*Bz - Az*By;
    this->normal[1] = Az*Bx - Ax*Bz;
    this->normal[2] = Ax*By - Ay*Bx;
}

double Triangle::getNormal(int i)
{
    if (i > 2) { qDebug() << "Index must be from [0,2]"; return 0;}
    return this->normal[i];
}

Triangle::~Triangle()
{
    delete points;
    delete normal;
}

