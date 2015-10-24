#ifndef RULEDSURFACE_H
#define RULEDSURFACE_H


class RuledSurface
{
public:
    RuledSurface();
    virtual double getX(double u, double w) = 0;
    virtual double getY(double u, double w) = 0;
    virtual double getZ(double u, double w) = 0;
    virtual double *getPoint(double u, double w) = 0;
    ~RuledSurface();
};

#endif // RULEDSURFACE_H
