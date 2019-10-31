#include "bsplinecurve.h"

BSplineCurve::BSplineCurve(std::vector<gsl::vec3> controlpoints, std::vector<float> knots, int degree)
    : c{controlpoints}, t{knots}, d{degree}
{

}

// Parametre inn:
// x - en parameterverdi på skjøtvektor
// my - et tall slik at t[my] <= x < t[my+1]
// Returverdi: et punkt på splinekurven
// b,n,d,t er objektvariable i klassen BSplineCurve
gsl::vec3 BSplineCurve::evaluateBSpline(int my, float x)
{
    std::vector<gsl::vec3> a; // forutsetter da at n+d+1 <= 20
    a.resize(t.size() + d + 1);

    for (int j=0; j<=d; j++)
        a[d-j] = c[my-j];

    for (int k=d; k>0; k--) {
        int j = my-k;
        for (int i=0; i<k; i++) {
            j++;
            float w = (x-t[j])/(t[j+k]-t[j]);
            a[i] = a[i] * (1-w) + a[i+1] * w;
        }
    }
    return a[0];
}

int BSplineCurve::getMy(float x)
{
    for (unsigned int i{0}; i < t.size() - 1; ++i)
        if (t[i] <= x && x < t[i + 1])
            return static_cast<int>(i);

    return -1;
}

std::vector<float> BSplineCurve::calcKnots() const
{
    auto startEndSize = static_cast<unsigned int>(d + 1);
    auto n = c.size() + startEndSize;

    // If following is true, spline curve is ill formed
    if (n < 2 * startEndSize)
        return {};

    auto innerSize = n - 2 * startEndSize;

    std::vector<float> t;
    t.reserve(n);

    for (unsigned int i{0}; i < n; ++i)
    {
        if (i < startEndSize)
            t.push_back(0.f);
        else if (n - startEndSize <= i)
            t.push_back(1.f);
        else
            t.push_back(static_cast<float>(i - startEndSize + 1) / (innerSize + 1));
    }

    return t;
}