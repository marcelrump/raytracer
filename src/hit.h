// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_HIT_H_
#define RAYTRACER_SRC_HIT_H_

#include "material.h"
#include "math.h"
#include "types.h"
#include "vector3.h"

struct Hit
{
  double distance = INF;
  Material material;
  V3 position;
  V3 normal;
};

#endif // RAYTRACER_SRC_HIT_H_
