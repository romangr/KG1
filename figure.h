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
    ~Figure();
};

#endif // FIGURE_H
