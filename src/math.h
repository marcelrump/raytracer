// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_MATH_H_
#define RAYTRACER_SRC_MATH_H_

#include <limits>

#define PI  3.1415926535979846f
#define EPS 1e-10
#define INF std::numeric_limits<double>::infinity()

inline double clamp(double x,
                    double min = 0.,
                    double max = 1.)
{
  return x < min ? min : x > max ? max : x;
}

#endif // RAYTRACER_SRC_MATH_H_
