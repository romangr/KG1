#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "matrix.h"
#include "curve.h"
#include <QVector>

class LineSegment : Curve
{
private:
    Matrix coords;

    int isInSegments(QVector<double> &begin, QVector<double> &end, double x);
    int fPoints[2];
public:
    Matrix *intersections;
    LineSegment(Matrix& m);
    LineSegment(double x1, double y1, double z1, double x2, double y2, double z2);
    double getX(double t);
    double getY(double t);
    double getZ(double t);
    double *getPoint(double t);
    double getCoord(int x, int y);
    double getTbyX(double x);
    void setFigurePoints(int x, int y);
    int getFigurePoint(int i);
    void addIntersection(double t1, double t2);
    Matrix calculateIntersections(); //заменить на объединение, должен посчитать объединение вырезаемых отрезков
    ~LineSegment();
};

#endif // LINESEGMENT_H
