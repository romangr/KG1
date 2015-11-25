#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H
#include "ruledsurface.h"
#include <QVector>
#include "triangle.h"
#include "linesegment.h"

class TriangleSurface
{
private:
    RuledSurface *surface;
    Figure *figure;
    Figure oldF;
    QVector<Triangle*> triangles;
    QVector<LineSegment*> lineSegments;
    int N;
public:
    TriangleSurface(int n);
    TriangleSurface(RuledSurface &r);
    void turn(char axis, double angle);
    Figure *getVisibleFigure();
    ~TriangleSurface();
};

#endif // TRIANGLESURFACE_H
