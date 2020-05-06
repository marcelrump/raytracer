// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_MATERIAL_H_
#define RAYTRACER_SRC_MATERIAL_H_

#include "types.h"
#include "vector3.h"

enum MaterialType { DIFFUSE_AND_GLOSSY,
                    REFLECTION_AND_REFRACTION,
                    REFLECTION_ONLY }; 

struct Material
{
  V3 color;
  MaterialType type = DIFFUSE_AND_GLOSSY;
  double ambient = 0.2;
  double diffuse = 0.5;
  double specular = 0.2;
  double glossiness = 25.;
};

#endif // RAYTRACER_SRC_MATERIAL_H_
