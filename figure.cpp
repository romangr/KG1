#include "figure.h"
#include <stdlib.h>
Figure::Figure()
{

}

Figure::~Figure()
{

}

void Figure::transform(Matrix &transformMatrix)
{
    //this->coords.*(this->coords, transformMatrix);
    //попробуй перемножь
}

void Figure::addPoint(double x, double y, double z)
{
    double line[4];
    line[0] = x;
    line[1] = y;
    line[2] = z;
    line[3] = 0;
    this->coords->addLine(3,line);
}
