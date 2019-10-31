#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include <vector>
#include "vector3d.h"


class BSplineCurve
{
public:
    // ikke alle disse funksjonene er nødvendige
    BSplineCurve(std::vector<gsl::vec3> controlpoints, std::vector<float> knots, int degree=2);
    gsl::vec3 evaluateBSpline(int my, float x);
    int getMy(float x);
    /**
     * Calculates knots for a bspline for a normal
     * bezier like distribution
     * @brief Calculates knots for a bspline
     * @return new knot vector
     */
    std::vector<float> calcKnots() const;

    std::vector<gsl::vec3> c;       // control points
    // int n;                       //n = number of knots
    std::vector<float> t;           // knots
    int d;                          // d = degree
};

#endif // BSPLINECURVE_H
