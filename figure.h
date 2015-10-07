#ifndef FIGURE_H
#define FIGURE_H
#include <QGenericMatrix>

class Figure
{
private:
    //эта зараза должна задаваться размерами предварительно
    //альтернатива - разбираться с неQT библиотекой lapack.
    //или самим написать класс матриц
    QGenericMatrix<8,4,double> coords;
    QGenericMatrix<8,4,bool> adjacency;
public:
    Figure();
    void transform(QGenericMatrix<8,4,double> &transformMatrix);
    void turn(char axis, double angle);
    void draw();
    ~Figure();
};

#endif // FIGURE_H
