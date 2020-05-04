// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "plane.h"

#include "math.h"

bool Plane::Intersect(const Ray &ray, Hit *hit) const
{
  // Check if plane and ray are parallel
  if (VectorProduct(normal_, ray.direction) == V3(0., 0., 0.))
    return false;

  // The intersection point I of a plane with related point P and normal n
  // and an incoming ray with origin O and direction d
  // can be parameterized in two different ways:
  //   I = O + t * d,
  //   (P - I) * n = 0,
  // where the travel distance is given by
  //   t = (P - O) * n / (d * n)
  double t = (p_ - ray.origin) * normal_ / (ray.direction * normal_);

  if (t < ray.t_min || t > ray.t_max)
    return false;
  
  hit->distance = t;
  hit->material = material_;
  hit->position = ray.origin + t * ray.direction;
  hit->normal   = normal_;
  return true;  
}
