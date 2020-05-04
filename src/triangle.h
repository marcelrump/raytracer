// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_TRIANGLE_H_
#define RAYTRACER_SRC_TRIANGLE_H_

#include "hit.h"
#include "material.h"
#include "primitive.h"
#include "ray.h"
#include "types.h"
#include "vector3.h"

class Triangle : public Primitive
{
  V3 a_;
  V3 b_;
  V3 c_;

 public:
  Triangle(const V3 &a,
           const V3 &b,
           const V3 &c,
           const Material &material);

  bool Intersect(const Ray &ray, Hit *hit) const;
};

#endif // RAYTRACER_SRC_TRIANGLE_H_
