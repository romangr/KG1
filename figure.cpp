#include "figure.h"
#include <stdlib.h>
#include <math.h>
Figure::Figure()
{
    coords = new Matrix();
    isFinalize = false;
}

Figure::Figure(Matrix &c)
{
    if(c.getWidth() != 4)
    {
        qDebug() << "Figure matrix must have 4 columns";
        this->coords = new Matrix();
        isFinalize = false;
        return;
    }
    this->coords = new Matrix(c);
    if (c.getElement(c.getHeight()-1, c.getWidth()-1) != 0)
    {
        isFinalize = true;
    } else
    {
       isFinalize = false;
    }

}

void Figure::printMatrix()
{
    this->coords->print();
}

Figure::~Figure()
{
    delete(coords);
}

void Figure::transform(Matrix &transformMatrix)
{
    //if (transformMatrix.getHeight() != 4 || transformMatrix.getWidth() != 4) {qDebug() << "Transform matrix have to be 4x4"; return;}
    if (!isFinalize) {qDebug() << "Figure must be finalized to be transformed"; return;}
    Matrix *newCoords = new Matrix();
    *newCoords = *(this->coords);
    delete(this->coords);
    *newCoords = *newCoords*transformMatrix;
    this->coords = newCoords;
}

void Figure::turn(char axis, double angle)
{
    Matrix transformMatrix;
    const double PI = acos(-1);
    qDebug() << PI;
    angle = angle * PI / 180;
    double sinA = sin(angle);
    double cosA = cos(angle);

    if (axis == 0) //x
    {
        transformMatrix.addLine(1,    0,     0, 0);
        transformMatrix.addLine(0, cosA, -sinA, 0);
        transformMatrix.addLine(0, sinA,  cosA, 0);
        transformMatrix.addLine(0,    0,     0, 1);
    }

    if (axis == 1) //y
    {
        transformMatrix.addLine( cosA, 0, sinA, 0);
        transformMatrix.addLine(    0, 1,    0, 0);
        transformMatrix.addLine(-sinA, 0, cosA, 0);
        transformMatrix.addLine(    0, 0,    0, 1);
    }

    if (axis == 2) //z
    {
        transformMatrix.addLine(cosA, -sinA, 0, 0);
        transformMatrix.addLine(sinA,  cosA, 0, 0);
        transformMatrix.addLine(0,        0, 1, 0);
        transformMatrix.addLine(0,        0, 0, 1);
    }

    this->transform(transformMatrix);
}

void Figure::finalize()
{
    double line[4];
    line[0] = 0;
    line[1] = 0;
    line[2] = 0;
    line[3] = 1;
    this->coords->addLine(4, line);
    this->isFinalize = true;
}

void Figure::addPoint(double x, double y, double z)
{
    if (this->isFinalize) {qDebug() << "Point can't be added to finilized matrix"; return;}
    /*double line[4];
    line[0] = x;
    line[1] = y;
    line[2] = z;
    line[3] = 0;
    this->coords->addLine(4,line);*/
    this->coords->addLine(x, y, z, 0);
}
