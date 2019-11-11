#ifndef TROPHY_H
#define TROPHY_H

// #include "octahedronball.h"
#include "objmesh.h"

class Trophy : public ObjMesh
{
public:
    Trophy();
    Trophy(const Trophy& t) = default;

    void init() override;
};

#endif // TROPHY_H
