#ifndef FIGURE_H
#define FIGURE_H
#include <QGenericMatrix>
#include "matrix.h"
class Figure
{
private:
    Matrix *coords;
    bool isFinalize;
    Matrix *adjacency;
public:
    Figure();
    Figure(Matrix& c);
    void printMatrix();
    void printAdjacency();
    void addPoint(double x,double y, double z);
    void editPoint(int point, double x, double y, double z);
    void setEdge(int point1, int point2, bool state);
    bool edgeExist(int point1, int point2);
    void transform(Matrix &transformMatrix);
    void turn(char axis, double angle);
    void draw();
    void finalize();
    ~Figure();
};

#endif // FIGURE_H
