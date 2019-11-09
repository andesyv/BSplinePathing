#include "npc.h"

NPC::NPC(BSplineCurve &&bsplinecurve, gsl::Vector3D color)
    : curve{std::move(bsplinecurve)}
{
    mMatrix.setToIdentity();
}

void NPC::readFile(std::string filename) {
    std::ifstream inn;
    inn.open(filename.c_str());

    if (inn.is_open())
    {
        unsigned long n;
        Vertex vertex;
        inn >> n;
        mVertices.reserve(n);
        for (unsigned long i=0; i<n; i++)
        {
            inn >> vertex;
            mVertices.push_back(vertex);
        }
        inn.close();
    }
    else
    {
        qDebug() << "Error: " << filename.c_str() << " could not be opened!";
    }
}

void NPC::patrol(float deltaT)
{
    t += deltaT * dir;
    if (0.98f <= t || t < 0.f)
    {
        t = gsl::clamp(t, 0.f, 1.f);
        dir = -dir;
    }

    auto p = curve(t);
    mMatrix.setPosition(p.x, p.y, p.z);
}

void NPC::draw()
{
    if (debugLine)
    {
        glPointSize(3.f);
        glBindVertexArray(splineVAO);
        glDrawArrays(GL_LINE_STRIP, 0, splineResolution);
        glDrawArrays(GL_POINTS, splineResolution, curve.getCs().size());
    }

    glBindVertexArray(NPCVAO);
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void NPC::draw(Shader *shader)
{
    if (debugLine)
    {
        gsl::Matrix4x4 mat{};
        mat.setToIdentity();
        glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "mMatrix"), 1, GL_TRUE, mat.constData());
        glPointSize(3.f);
        glBindVertexArray(splineVAO);
        glDrawArrays(GL_LINE_STRIP, 0, splineResolution);
        glDrawArrays(GL_POINTS, splineResolution, curve.getCs().size());
    }

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "mMatrix"), 1, GL_TRUE, mMatrix.constData());
    glBindVertexArray(NPCVAO);
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
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
    readFile("../BSplinePathing/Assets/ball.txt");

    glGenVertexArrays(1, &NPCVAO);
    glBindVertexArray(NPCVAO);

    glGenBuffers(1, &NPCVBO);
    glBindBuffer(GL_ARRAY_BUFFER, NPCVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof (Vertex), mVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid*)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (GLvoid*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    mInited = true;
}

void NPC::updatePathVisual()
{
    std::vector<Vertex> vertices;
    auto c = curve.getCs();
    vertices.reserve(splineResolution + c.size());

    for (int i{0}; i < splineResolution; ++i)
    {
        auto p = curve(i * 1.f / splineResolution);
        vertices.emplace_back(p.x, p.y, p.z, 0.f, 1.f, 0.f);
    }

    // Control points
    for (int i{0}; i < c.size(); ++i)
    {
        auto p = c.at(i);
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
