// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "sphere.h"

#include <cmath>

bool Sphere::Intersect(const Ray &ray, Hit *hit) const
{
  // Each point P on a sphere with center C and radius r
  // must satisfy the vector equation given by
  //   (P - C)² - r² = 0.
  // An incoming ray can be parameterized as
  //   P = O + t * d,
  // with origin O and direction d.
  // Intersections between them can be calculated by
  // solving a second-degree polynomial.

  V3 co = ray.origin - center_;

  // a = d * d (= 1 if d normalized)
  double a = ray.direction * ray.direction;

  // b = 2d * (O - C)
  double b = 2. * ray.direction * co;

  // c = (O - C) * (O - C) - r²
  double c = co * co - radius_ * radius_;

  // TODO(marcel): This calculation of the discriminant Delta can be optimized
  // and may even be optimized automatically by the compiler,
  // but for the sake of clarity is given here in its full form.
  double delta = b * b - 4. * a * c;

  if (delta < 0) return false; // Ray missed the sphere
  else delta = sqrt(delta);
  
  // TODO(marcel): This could be optimized as well.
  double t_1 = (-b - delta) / (2. * a);
  double t_2 = (-b + delta) / (2. * a);

  // Check if intersection point lies within the ray interval.
  if (t_2 < ray.t_min) return false; // Sphere is too close
  if (t_1 > ray.t_max) return false; // Sphere is too far away
  if (t_1 < ray.t_min && t_2 > ray.t_max) return false;

  double t = t_1 < ray.t_min ? t_2 : t_1;
  hit->distance = t;
  hit->material = material_;
  hit->position = ray.origin + t * ray.direction;
  hit->normal   = Norm3(hit->position - center_);
  return true;
}
