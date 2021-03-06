// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_RAY_H_
#define RAYTRACER_SRC_RAY_H_

#include "math.h"
#include "types.h"
#include "vector3.h"

struct Ray
{
  V3 origin;
  V3 direction;
  double t_min = EPS;
  double t_max = INF;
};

#endif // RAYTRACER_SRC_RAY_H_
