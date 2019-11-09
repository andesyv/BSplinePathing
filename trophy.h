#ifndef TROPHY_H
#define TROPHY_H

#include "octahedronball.h"

class Trophy : public OctahedronBall
{
public:
    Trophy();
    Trophy(const Trophy& t) = default;
};

#endif // TROPHY_H
