#include "matrix.h"
#include <qdebug.h>
#include <iostream>
Matrix::Matrix()
{

}

Matrix::Matrix(int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        QVector<double>* buf = new QVector<double>();
        for (int j = 0; j < n; j++)
        {
            buf->push_back(0);
        }
        this->m.push_back(*buf);
        delete(buf);
    }
}

void Matrix::print()
{
    std::cout << "\n";
    for (int i = 0; i < this->getHeight(); i++)
    {
        for (int j = 0; j < this->getWidth(); j++)
        {
            /*qDebug()*/ std::cout << this->getElement(i, j) << " ";
        }
        std::cout << "\n";
    }
}


int Matrix::getWidth()
{
    if (m.size() > 0)
    {
        return m.at(0).size();
    }
    return 0;
}

int Matrix::getHeight()
{
    return m.size();
}

double Matrix::getElement(int x, int y)
{
    if (x < this->getHeight() && y < this->getWidth())
    {
        return this->m.at(x).at(y);
    }
    return 0;
}

Matrix &Matrix::operator*(Matrix &a)
{
    Matrix *newMatrix = new Matrix();
    if (this->getWidth() == a.getHeight())
    {
        int m = this->getHeight();
        int n = this->getWidth();
        int m1 = a.getHeight();
        int n1 = a.getWidth();
        QVector<double>* buf = new QVector<double>();
        for (int i = 0; i < m; i++)
        {
            newMatrix->m.push_back(*buf);
            for (int j = 0; j < n1; j++)
            {
                int element = 0;
                for (int k = 0; k < n; k++)
                {
                    element += this->getElement(i, k) * a.getElement(k, j);
                }
                newMatrix->m[i].push_back(element);
            }
        }
        delete(buf);
    }
    return *newMatrix;
}

void Matrix::addLine(int n, double *a)
{
    if (!(n == this->getWidth() || this->getWidth() == 0)) return;
    double *buf0 = a;
    QVector<double>* buf = new QVector<double>();
    for (int i = 0; i < n; i++)
    {
        buf->push_back(*buf0);
        buf0++;

    }
    this->m.push_back(*buf);
    delete(buf);
}

void Matrix::addLine(double a, double b, double c, double d)
{
    if (this->getWidth() != 4 && this->getWidth() != 0) {return;}
    QVector<double>* buf = new QVector<double>();
    buf->push_back(a);
    buf->push_back(b);
    buf->push_back(c);
    buf->push_back(d);
    this->m.push_back(*buf);
    delete(buf);
}

Matrix::~Matrix()
{

}

