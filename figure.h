#ifndef FIGURE_H
#define FIGURE_H
#include <QGenericMatrix>

class Figure
{
private:
    QGenericMatrix<double> coords;
    QGenericMatrix<bool> adjacency;
public:
    Figure();
    void transform(QGenericMatrix &transformMatrix);
    void turn(char axis, double angle);
    void draw();
    ~Figure();
};

#endif // FIGURE_H
