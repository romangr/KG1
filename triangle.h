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
    bool isUnderTriangle(double a, double b, double c);
    bool isApex(int pointNumber);
    Matrix pointNumbers;
    ~Triangle();
};

#endif // TRIANGLE_H
