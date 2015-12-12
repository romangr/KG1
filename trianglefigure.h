#ifndef TRIANGLEFIGURE_H
#define TRIANGLEFIGURE_H
#include "figure.h"
#include "triangle.h"
#include <qvector.h>

class TriangleFigure : public Figure
{
private:
    QVector<Triangle*> triangles;
    int getPlaneSide(Triangle *triangle);
    double maxCoord;
public:
    TriangleFigure();
    void addTriangle(Triangle* tr);
    void draw(QPaintDevice *device);
    ~TriangleFigure();
};

#endif // TRIANGLEFIGURE_H
