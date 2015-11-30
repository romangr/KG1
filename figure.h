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
    double frontViewScale;
public:
    Figure();
    Figure(Matrix& c);    
    Matrix getFrontView();
    void printMatrix();
    void printAdjacency();
    void addPoint(double x,double y, double z);
    void editPoint(int point, double x, double y, double z);
    double getCoord(int point, int coord);
    int getSize();
    double getScale();
    void setScale(double scale);
    void setEdge(int point1, int point2, bool state);
    void cutPoint(int point);
    bool edgeExist(int point1, int point2);
    void transform(Matrix &transformMatrix);
    void turn(char axis, double angle);
    void autoscale_basicXY(QPaintDevice *device);
    void autoscale_parabols(QPaintDevice *device,int k);
    void draw(QPaintDevice *device);
    void roundCoords();
    Figure *getCopy();
    ~Figure();
};

#endif // FIGURE_H
