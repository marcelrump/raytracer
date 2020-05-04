// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_PRIMITIVE_H_
#define RAYTRACER_SRC_PRIMITIVE_H_

#include "hit.h"
#include "material.h"
#include "ray.h"
#include "types.h"
#include "vector3.h"

class Primitive
{
 protected:
  Primitive(const Material &material)
   : material_(material) {}

 public:
  Material material_;

  virtual ~Primitive() = default;

  virtual bool
  Intersect(const Ray &ray, Hit *hit) const = 0;
};

#endif // RAYTRACER_SRC_PRIMITIVE_H_
