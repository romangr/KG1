#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "matrix.h"
#include <cmath>
#include <qdebug.h>

class Triangle
{
private:
    Matrix *points;
    Matrix pointNumbers;
public:
    Triangle(Matrix &m, double a, double b, double c);
    bool isUnderTriangle(double a, double b, double c);
    bool isApex(int pointNumber);
    ~Triangle();
};

#endif // TRIANGLE_H
