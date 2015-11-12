#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H
#include "ruledsurface.h"
#include <QVector>
#include "triangle.h"

class TriangleSurface
{
private:
    RuledSurface *surface;
    Figure *figure;
    Figure oldF;
    QVector<Triangle*> triangles;
    int N;
public:
    TriangleSurface(RuledSurface &r);
    void turn(char axis, double angle);
    Figure *getVisibleFigure();
    ~TriangleSurface();
};

#endif // TRIANGLESURFACE_H
