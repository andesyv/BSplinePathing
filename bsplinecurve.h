#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <vector>
#include "vector3d.h"


class BSplineCurve
{
public:
    BSplineCurve(const std::vector<gsl::vec3> &controlpoints, int degree=2);
    BSplineCurve(const std::vector<gsl::vec3> &controlpoints, std::vector<float> knots, int degree=2);
    gsl::vec3 evaluateBSpline(int my, float x) const;
    int getMy(float x) const;
    /**
     * Calculates knots for a bspline for a normal
     * bezier like distribution
     * @brief Calculates knots for a bspline
     * @return new knot vector
     */
    std::vector<float> calcKnots() const;

    gsl::vec3 eval(float x) const;
    gsl::vec3 operator()(float x) const;


    std::vector<gsl::vec3> getCs() const;
    gsl::vec3& atC(unsigned int index);
    void setCs(const std::vector<gsl::vec3>& cs);


    // Member variables
private:
    std::vector<gsl::vec3> c;       // control points

public:
    int d;                          // d = degree
    std::vector<float> t;           // knots
    bool autoCalcKnots = true;


    ~BSplineCurve() = default;
};

#endif // BSPLINECURVE_H
