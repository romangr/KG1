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
    double maxBrightness;
public:
    TriangleFigure();
    void addTriangle(Triangle* tr);
    void turn(char axis, double angle);
    void draw(QPaintDevice *device);
    ~TriangleFigure();
};

#endif // TRIANGLEFIGURE_H
