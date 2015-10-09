#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>

class Matrix
{
private:
    QVector< QVector<double> > m;
public:
    Matrix();
    Matrix(int m, int n);
    void print();
    void addLine(int n, double* a);
    void addLine(double a, double b, double c, double d);
    int getWidth();
    int getHeight();
    double getElement(int x, int y);
    Matrix& operator*(Matrix& a);
    ~Matrix();
};

#endif // MATRIX_H
