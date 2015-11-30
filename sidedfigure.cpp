#include "sidedfigure.h"

SidedFigure::SidedFigure()
{

}

/*void SidedFigure::setEdge(int point1, int point2, int side) // {1..N}
{
    double element;
    switch(side)
    {
    case 2: element = 4; break;
    case 1: element = 2; break;
    case 0: element = 0; break;
    }

    if (point1 > point2) //зачем?
    {
        int c = point1;
        point1 = point2;
        point2 = c;
    }

    this->adjacency->setElement(point1-1, point2-1, element);
    this->adjacency->setElement(point2-1, point1-1, element);
}

int SidedFigure::getEdge(int point1, int point2) // {0..(N-1)}
{
    if (this->adjacency->getElement(point1, point2) < 1)
    {
        return 0;
    } else
    {
        if (this->adjacency->getElement(point1, point2) < 3)
        {
            return 1;
        } else
        {
            return 2;
        }
    }
}*/

SidedFigure::~SidedFigure()
{

}

