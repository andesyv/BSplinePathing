#include "npc.h"

NPC::NPC(BSplineCurve &&bsplinecurve, gsl::Vector3D color)
    : curve{std::move(bsplinecurve)}
{
    mMatrix.setToIdentity();
}

void NPC::draw()
{
    if (debugLine)
    {
        glPointSize(3.f);
        glBindVertexArray(splineVAO);
        glDrawArrays(GL_LINE_STRIP, 0, splineResolution);
        glDrawArrays(GL_POINTS, splineResolution, curve.c.size());
    }
}

void NPC::init()
{
    initializeOpenGLFunctions();

    // Spline curve
    glGenVertexArrays(1, &splineVAO);
    glBindVertexArray(splineVAO);

    glGenBuffers(1, &splineVBO);
    glBindBuffer(GL_ARRAY_BUFFER, splineVBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid*)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Send the actual vertex data
    updatePathVisual();


    // NPC
    glGenVertexArrays(1, &NPCVAO);
    glBindVertexArray(NPCVAO);

    glGenBuffers(1, &NPCVBO);
    glBindBuffer(GL_ARRAY_BUFFER, NPCVBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void NPC::updatePathVisual()
{
    // Temp
    curve.c = {
        {0.f, 3.f, 0.f},
        {2.f, -2.f, 0.f},
        {3.f, -5.f, 0.f},
        {5.f, 2.f, 0.f},
        {7.f, 3.f, 0.f}
    };
    curve.t = curve.calcKnots();


    std::vector<Vertex> vertices;
    vertices.reserve(splineResolution + curve.c.size());

    for (int i{0}; i < splineResolution; ++i)
    {
        auto p = curve(i * 1.f / splineResolution);
        vertices.emplace_back(p.x, p.y, p.z, 0.f, 1.f, 0.f);
    }

    // Control points
    for (int i{0}; i < curve.c.size(); ++i)
    {
        auto p = curve.c.at(i);
        vertices.emplace_back(p.x, p.y, p.z, 1.f, 0.f, 0.f);
    }

    glBindVertexArray(splineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, splineVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

NPC::~NPC()
{
    glDeleteBuffers(1, &splineVBO);
    glDeleteVertexArrays(1, &splineVAO);

    glDeleteBuffers(1, &NPCVBO);
    glDeleteVertexArrays(1, &splineVAO);
}
