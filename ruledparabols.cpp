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

Figure* RuledParabols::getFigure(int k)
{
    double step = 1.0/k;
    double i0 = 0;
    double j0 = 0;
    Figure *f = new Figure();
    for (int i = 0; i <= k; i++)
    {
        j0 = 0;
        for (int j = 0; j <= k; j++)
        {
            f->addPoint(getX(i0, j0), getY(i0, j0), getZ(i0, j0));
            if (j0 > 0) {
                f->setEdge((k+1)*i + j, (k+1)*i + j + 1, true);
            }

            if (i0 > 0) {
                f->setEdge((k+1)*i + j + 1, (k+1)*(i-1) + j + 1, true);
            }
            j0+=step;
        }
        i0+=step;
    }
    return f;
}

RuledParabols::~RuledParabols()
{

}

