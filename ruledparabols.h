#ifndef RULEDPARABOLS_H
#define RULEDPARABOLS_H
#include "parabola.h"
#include "ruledsurface.h"
#include "figure.h"

class RuledParabols : public RuledSurface
{
private:
    Parabola *p1;
    Parabola *p2;
public:
    RuledParabols(Parabola& p1, Parabola& p2);
    double getX(double u, double w);
    double getY(double u, double w);
    double getZ(double u, double w);
    double *getPoint(double u, double w);
    Figure getFigure(double k);
    ~RuledParabols();
};

#endif // RULEDPARABOLS_H
