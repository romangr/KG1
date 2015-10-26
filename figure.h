#ifndef FIGURE_H
#define FIGURE_H
#include <QGenericMatrix>
#include <QPainter>
#include "matrix.h"
class Figure
{
private:
    Matrix *adjacency;
    Matrix *coords;
    Matrix *coords_last;
    Matrix *coords_before_last;

    double frontViewScale;
public:
    Figure();
    Figure(Matrix& c);
    //1=last, 2=before_last, default=current
    Matrix getFrontView(int state);
    void printMatrix();
    void printAdjacency();
    void addPoint(double x,double y, double z);
    void editPoint(int point, double x, double y, double z);
    void setEdge(int point1, int point2, bool state);
    bool edgeExist(int point1, int point2);
    void transform(Matrix &transformMatrix);
    void turn(char axis, double angle);
    void autoscale(QPaintDevice *device);
    void draw(QPaintDevice *device);
    void resetLastCoord();
    ~Figure();
};

#endif // FIGURE_H
