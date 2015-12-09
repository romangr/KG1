#ifndef LIGHTEDSURFACE_H
#define LIGHTEDSURFACE_H
#include "triangle.h"
#include "ruledsurface.h"
#include <QLinkedList>

class LightedSurface
{
private:
    RuledSurface *surface;
    Figure *figure;
    Figure *originalFigure;
    QVector<Triangle*> triangles;
    //QLinkedList<Triangle*> sortedTriangles;
    void fillTriangles();
    int getPlaneSide(Triangle *triangle);
    int N;
    //void addTriangleToSorted(Triangle *triangle);
    //bool debug;
public:
    void addTriangleToSorted(Triangle *triangle); //временно public
    QLinkedList<Triangle*> sortedTriangles;
    LightedSurface();
    LightedSurface(RuledSurface &r, int N);
    ~LightedSurface();
};

#endif // LIGHTEDSURFACE_H
