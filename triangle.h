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
    bool isUnderTriangle(double a, double b, double c); //за плоскостью и в проекции треугольника
    bool isUnderTrianglePlane(double a, double b, double c);
    bool isUnderTrianglePlane(Triangle *triangle);
    bool isBehindTriangle(double z); //за треугольником, дальше вершин. НЕНАДО
    bool isInFrontOfTriangle(double z);
    bool isInProjection(double a, double b);
    bool isApex(int pointNumber);
    bool isEdge(LineSegment *ls);
    bool doesIntersectPlane(LineSegment *lineSegment);
    bool hasMutualEdge(Triangle *triangle);
    LineSegment *getSide(int i);
    double getZmax();
    double getZmin();
    double getXmax();
    double getXmin();
    double getYmax();
    double getYmin();
    double getPlaneIntersectPoint(LineSegment *lineSegment);
    bool isToRightOrToLeft(Triangle *triangle);
    bool isAboveOrBelow(Triangle *triangle);
    double getCoord(int x, int y);
    void setNormal(int point1, int point2, int point3, int point4);
    double getNormal(int i);
    Matrix pointNumbers;
    ~Triangle();
};

#endif // TRIANGLE_H
