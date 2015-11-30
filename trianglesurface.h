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
    Figure *originalFigure;
    QVector<Triangle*> triangles;
    QVector<LineSegment*> lineSegments;
    void fillTriangles();
    void fillLineSegments();
    int N;
    bool debug;
public:
    TriangleSurface();
    TriangleSurface(RuledSurface &r);
    TriangleSurface(RuledSurface &r, int N);
    void turn(char axis, double angle);
    Figure *getVisibleFigure(double scale = 1);
    ~TriangleSurface();
};

#endif // TRIANGLESURFACE_H
