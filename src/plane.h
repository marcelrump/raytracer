// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_PLANE_H_
#define RAYTRACER_SRC_PLANE_H_

#include "hit.h"
#include "material.h"
#include "primitive.h"
#include "types.h"
#include "ray.h"
#include "vector3.h"

class Plane : public Primitive
{
  V3 p_;
  V3 normal_;

 public:
  Plane(const V3 &p,
        const V3 &normal,
        const Material &material)
   : p_(p), normal_(Norm3(normal)), Primitive(material) {}

  bool Intersect(const Ray &ray, Hit *hit) const;
};

#endif // RAYTRACER_SRC_PLANE_H_
