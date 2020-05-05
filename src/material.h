// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_MATERIAL_H_
#define RAYTRACER_SRC_MATERIAL_H_

#include "types.h"
#include "vector3.h"

struct Material
{
  V3 color;
  double ambient = 0.2;
  double diffuse = 0.5;
  double specular = 0.1;
  double glossiness = 100.;
};

#endif // RAYTRACER_SRC_MATERIAL_H_
