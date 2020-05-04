// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_SPHERE_H_
#define RAYTRACER_SRC_SPHERE_H_

#include "hit.h"
#include "material.h"
#include "primitive.h"
#include "ray.h"
#include "types.h"
#include "vector3.h"

class Sphere : public Primitive
{
  double radius_;
  V3 center_;

 public:
  Sphere(double radius,
         const V3 &center,
         const Material &material)
   : radius_(radius), center_(center), Primitive(material) {}

  bool Intersect(const Ray &ray, Hit *hit) const;
};

#endif // RAYTRACER_SRC_SPHERE_H_
