#include "ruledparabols.h"

RuledParabols::RuledParabols(Parabola &p1, Parabola &p2)
{
    this->p1 = new Parabola(p1);
    this->p2 = new Parabola(p2);
}

double RuledParabols::getX(double u, double w)
{
    return (1-w)*p1->getX(u) + w*p2->getX(u);
}

double RuledParabols::getY(double u, double w)
{
    return (1-w)*p1->getY(u) + w*p2->getY(u);
}

double RuledParabols::getZ(double u, double w)
{
    return (1-w)*p1->getZ(u) + w*p2->getZ(u);
}

double *RuledParabols::getPoint(double u, double w)
{
    double *point = new double[4];
    point[0] = getX(u, w);
    point[1] = getY(u, w);
    point[2] = getZ(u, w);
    point[3] = 0;
    return point;
}

Figure* RuledParabols::getFigure(double k)
{
    double step = 1.0/k;
    int i0 = 0;
    int j0 = 0;
    Figure *f = new Figure();
    for (double i = 0; i <= 1; i += step)
    {
        j0 = 0;
        for (double j = 0; j <= 1; j += step)
        {
            f->addPoint(getX(i, j), getY(i, j), getZ(i, j));
            if (j0 > 0) {
                f->setEdge((k+1)*i0 + j0, (k+1)*i0 + j0 + 1, true);
            }
            if (i0 > 0) {
                f->setEdge((k+1)*i0 + j0 + 1, (k+1)*(i0-1) + j0 + 1, true);
            }
            j0++;
        }
        i0++;
    }

    return f;
}

RuledParabols::~RuledParabols()
{

}

