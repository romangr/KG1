#ifndef RULEDPARABOLS_H
#define RULEDPARABOLS_H
#include "parabola.h"
#include "ruledsurface.h"
#include "figure.h"

class RuledParabols : public RuledSurface
{
public:
    RuledParabols(Parabola& p1, Parabola& p2);
    ~RuledParabols();
};

#endif // RULEDPARABOLS_H
