#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "matrix.h"
#include <cmath>
#include <qdebug.h>
#include "linesegment.h"

class Triangle
{
private:
    Matrix *points;
    double *normal;

public:
    Triangle(Matrix &m, double a, double b, double c);
    Triangle(Triangle &tri);
    bool isUnderTriangle(double a, double b, double c); //за плоскостью
    bool isBehindTriangle(double z); //за треугольником, дальше вершин. НЕНАДО
    bool isInFrontOfTriangle(double z);
    bool isInProjection(double a, double b);
    bool isApex(int pointNumber);
    bool isEdge(LineSegment *ls);
    double getCoord(int x, int y);
    void setNormal(int point1, int point2, int point3, int point4);
    double getNormal(int i);
    Matrix pointNumbers;
    ~Triangle();
};

#endif // TRIANGLE_H
