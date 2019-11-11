#ifndef PLAYER_H
#define PLAYER_H

#include "objmesh.h"

class Player : public ObjMesh
{
public:
    Player();

    gsl::vec3 pos{0.f, 0.f, 0.f};
};

#endif // PLAYER_H
