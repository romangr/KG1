#ifndef LIGHTEDSURFACE_H
#define LIGHTEDSURFACE_H
#include "triangle.h"
#include "ruledsurface.h"

class LightedSurface
{
private:
    RuledSurface *surface;
    Figure *figure;
    Figure *originalFigure;
    QVector<Triangle*> triangles;
    QVector<Triangle*> sortedTriangles;
    void fillTriangles();
    int getPlaneSide(Triangle *triangle);
    int N;
    void addTriangleToSorted(Triangle *triangle);
    //bool debug;
public:
    LightedSurface();
    LightedSurface(RuledSurface &r, int N);
    ~LightedSurface();
};

#endif // LIGHTEDSURFACE_H
