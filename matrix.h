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
    void addLine(int n, double* a);
    int getWidth();
    int getHeight();
    double getElement(int x, int y);
    Matrix& operator*(Matrix& a);
    ~Matrix();
};

#endif // MATRIX_H
