#ifndef NPC_H
#define NPC_H
#include <queue>
#include "visualobject.h"
#include "gsl_math.h"
#include "bsplinecurve.h"
#include <chrono>
#include <optional>

class BSplineCurve;

class NPC : public VisualObject
{
public:
    enum NPCstates {SLEEP, PATROL, LEARN, CHASE};
    enum NPCevents {ENDPOINT_ARRIVED, ITEM_TAKEN, OBSTACLE_DETECTED, PLAYER_DETECTED, CHASE_ENDPOINT_ARRIVED};

public:
    NPC(BSplineCurve&& bsplinecurve, gsl::Vector3D color = gsl::Vector3D{1.0, 0.0, 0.0});
    void readFile(std::string filename);
    // void update(float t=0.05f); //t ikke brukt i funksjonen
    void initVertexBufferObjects();

    std::optional<NPCevents> patrol(float deltaT);
    void update();

    bool debugLine = true;
    void draw() override;
    void draw(Shader *shader) override;
    void init() override;

    BSplineCurve curve;

    void updatePathVisual();

    ~NPC() override;
private:
    NPCstates state{PATROL};

    int splineResolution = 50.f;
    float t{0};
    int dir{1};
    bool mapPathToTerrain = true;
    std::chrono::system_clock::time_point lastTime{std::chrono::system_clock::now()};
    double calcDeltaTime();

    GLuint NPCVAO;
    GLuint splineVAO;

    GLuint NPCVBO, splineVBO;
};

#endif // NPC_H
