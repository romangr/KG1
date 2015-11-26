#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "matrix.h"
#include <cmath>
#include <qdebug.h>

class Triangle
{
private:
    Matrix *points;

public:
    Triangle(Matrix &m, double a, double b, double c);
    bool isUnderTriangle(double a, double b, double c); //за плоскостью
    bool isBehindTriangle(double z); //за треугольником, дальше вершин. НЕНАДО
    bool isInFrontOfTriangle(double z);
    bool isInProjection(double a, double b);
    bool isApex(int pointNumber);
    double getCoord(int x, int y);
    Matrix pointNumbers;
    ~Triangle();
};

#endif // TRIANGLE_H
