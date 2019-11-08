#ifndef NPC_H
#define NPC_H
#include <queue>
#include "visualobject.h"
#include "gsl_math.h"
#include "bsplinecurve.h"


class BSplineCurve;

enum NPCstates {SLEEP, PATROL, LEARN, CHASE};
enum NPCevents {ENDPOINT_ARRIVED, ITEM_TAKEN, OBSTACLE_DETECTED, PLAYER_DETECTED, CHASE_ENDPOINT_ARRIVED};

class NPC : public VisualObject
{
public:
    NPC(BSplineCurve&& bsplinecurve, gsl::Vector3D color = gsl::Vector3D{1.0, 0.0, 0.0});
    void patrol();
    void learn();
    void readFile(std::string filename);
    // void update(float t=0.05f); //t ikke brukt i funksjonen
    void initVertexBufferObjects();

    bool debugLine = true;
    void draw() override;
    void init() override;

    BSplineCurve curve;

    void updatePathVisual();

    ~NPC() override;
private:
    int splineResolution = 50.f;

    GLuint NPCVAO;
    GLuint splineVAO;

    GLuint NPCVBO, splineVBO;
};

#endif // NPC_H
