#include "trophy.h"

Trophy::Trophy()
    : ObjMesh{"../BSplinePathing/Assets/star.obj"}
{

}

void Trophy::init()
{
    for (auto &v : mVertices)
        v.set_rgb(1.f, 1.f, 0.f);

    ObjMesh::init();
}

