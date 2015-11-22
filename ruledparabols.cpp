#include "ruledparabols.h"

RuledParabols::RuledParabols(Parabola &p1, Parabola &p2)
{
    this->p1 = new Parabola(p1);
    this->p2 = new Parabola(p2);
}

RuledParabols::~RuledParabols()
{
    /*delete(this->p1);
    delete(this->p2);*/
}

