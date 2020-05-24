// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_MATERIAL_H_
#define RAYTRACER_SRC_MATERIAL_H_

#include "types.h"
#include "vector3.h"

enum MaterialType { DIFFUSE_AND_GLOSSY,
                    REFLECTIVE, 
                    REFLECTIVE_AND_REFRACTIVE};

struct Material
{
  V3 color;
  V3 emission;
  MaterialType type = DIFFUSE_AND_GLOSSY;
};

#endif // RAYTRACER_SRC_MATERIAL_H_
