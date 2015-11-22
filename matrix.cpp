#include "matrix.h"
#include <qdebug.h>
#include <iostream>
#include <cmath>
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
            /*qDebug()*/std::cout << this->getElement(i, j) << " ";
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

void Matrix::setElement(int x, int y, double element)
{
    if (x < this->getHeight() && y < this->getWidth())
    {
        (this->m[x])[y] = element;
    }
}

void Matrix::enlarge()
{
    int size = this->getHeight();
    if (size != this->getWidth()) {return;}
    QVector<double>* buf = new QVector<double>();
    for (int i = 0; i < size; i++)
    {
        buf->push_back(0);
        this->m[i].push_back(0);
    }
    buf->push_back(0);
    this->m.push_back(*buf);
    delete(buf);
}

Matrix Matrix::operator*(Matrix &a)
{
    const double EPSILON = 0.000000000001;
    Matrix newMatrix0;
    Matrix *newMatrix = &newMatrix0;
    if (this->getWidth() == a.getHeight())
    {
        int m = this->getHeight();
        int n = this->getWidth();
        //int m1 = a.getHeight();
        int n1 = a.getWidth();
        QVector<double>* buf = new QVector<double>();
        for (int i = 0; i < m; i++)
        {
            newMatrix->m.push_back(*buf);
            for (int j = 0; j < n1; j++)
            {
                double element = 0;
                for (int k = 0; k < n; k++)
                {
                    if (fabs(this->getElement(i, k)) > EPSILON && fabs(a.getElement(k, j)) > EPSILON)
                    element += this->getElement(i, k) * a.getElement(k, j);
                }
                if (fabs(element) > EPSILON)
                {
                    newMatrix->m[i].push_back(element);
                } else
                {
                    newMatrix->m[i].push_back(0);
                }
            }
        }
        delete(buf);
    }
    return newMatrix0;
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

void Matrix::deleteLine(int index)
{
    if (this->getHeight() > 0) this->m.removeAt(index);
}

void Matrix::mult_scalar(double d)
{
    int m = this->getHeight();
    int n = this->getWidth();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            this->setElement(i, j, d * this->getElement(i,j));
        }
    }
}

//make me better (find max for every column)
void Matrix::findMaxXYZ(double& x,double& y, double& z)
{
    double xmax = abs(this->getElement(0,0));
    double ymax = abs(this->getElement(0,1));
    double zmax = abs(this->getElement(0,2));

    double m;

    for (int i=1; i< this->getHeight(); i++)
    {
        m=abs(this->getElement(i,0));
        if (m>xmax) {xmax = m;}

        m=abs(this->getElement(i,1));
        if (m>ymax) {ymax = m;}

        m=abs(this->getElement(i,2));
        if (m>zmax) {zmax = m;}
    }
    x = xmax;
    y = ymax;
    z = zmax;
}

Matrix::~Matrix()
{

}

