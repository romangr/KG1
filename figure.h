#ifndef FIGURE_H
#define FIGURE_H
#include <QGenericMatrix>
#include "matrix.h"
class Figure
{
private:
    Matrix *coords;
    //QGenericMatrix<m,n,bool> *adjacency;
public:
    Figure();
    void addPoint(double x,double y, double z);
    void transform(Matrix &transformMatrix);
    void turn(char axis, double angle);
    void draw();
    ~Figure();
};

#endif // FIGURE_H
