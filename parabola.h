#ifndef PARABOLA_H
#define PARABOLA_H
#include "matrix.h"
#include "curve.h"

class Parabola : public Curve
{
private:
    Matrix *points;
    double Ax0, Ax1, Ax2;
    double Ay0, Ay1, Ay2;
    double Az0, Az1, Az2;
public:
    Parabola(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
    double getX(double t);
    double getY(double t);
    double getZ(double t);
    double *getPoint(double t);
    ~Parabola();
};

#endif // PARABOLA_H
