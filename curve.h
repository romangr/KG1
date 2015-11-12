#ifndef CURVE_H
#define CURVE_H


class Curve
{
public:
    Curve();
    virtual double getX(double t) = 0;
    virtual double getY(double t) = 0;
    virtual double getZ(double t) = 0;
    virtual double *getPoint(double t) = 0;
    ~Curve();
};

#endif // CURVE_H
