#include "figure.h"
#include <stdlib.h>
Figure::Figure()
{
    coords = new Matrix();
    isFinalize = false;
}

Figure::Figure(Matrix &c)
{
    this->coords = new Matrix(c);
    isFinalize = false;
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
    Matrix *newCoords = new Matrix();
    *newCoords = *(this->coords);
    delete(this->coords);
    *newCoords = *newCoords*transformMatrix;
    this->coords = newCoords;
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
    double line[4];
    line[0] = x;
    line[1] = y;
    line[2] = z;
    line[3] = 0;
    this->coords->addLine(4,line);
}
