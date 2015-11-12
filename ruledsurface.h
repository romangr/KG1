#ifndef RULEDSURFACE_H
#define RULEDSURFACE_H
#include "curve.h"
#include "figure.h"

class RuledSurface
{
protected:
    Curve *p1;
    Curve *p2;
public:
    RuledSurface();
    double getX(double u, double w);
    double getY(double u, double w);
    double getZ(double u, double w);
    double *getPoint(double u, double w);
    Figure* getFigure(int k);
    ~RuledSurface();
};

#endif // RULEDSURFACE_H
