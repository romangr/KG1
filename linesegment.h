#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "matrix.h"
#include "curve.h"

class LineSegment : Curve
{
private:
    Matrix coords;
    Matrix *intersections;
public:
    LineSegment(Matrix& m);
    LineSegment(double x1, double y1, double z1, double x2, double y2, double z2);
    double getX(double t);
    double getY(double t);
    double getZ(double t);
    double *getPoint(double t);
    double getCoord(int x, int y);
    double getTbyX(double x);
    void addIntersection(double t1, double t2);
    double *calculateIntersections(); //заменить на объединение, должен посчитать объединение вырезаемых отрезков
    ~LineSegment();
};

#endif // LINESEGMENT_H
