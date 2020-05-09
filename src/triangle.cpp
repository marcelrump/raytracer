// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "triangle.h"

#include <cassert>
#include <cmath>

#include "math.h"

Triangle::Triangle(const V3 &a,
                   const V3 &b,
                   const V3 &c,
                   const Material &material)
 : a_(a), b_(b), c_(c), Primitive(material)
{
  // A triangle must consist of 3 distinct points A,B and C
  assert(VectorProduct(a - c, b - c) != V3(0., 0., 0.));
}

bool Triangle::Intersect(const Ray &ray, Hit *hit) const
{
  // Möller-Trumbore algorithm:
  // The intersection point P of a triangle with vertices A, B and C
  // and an incoming ray with origin O and direction d,
  // can be parameterized in two different ways:
  //   P = O + t * d,
  //   P = uA + vB + wC,
  // with
  //   u + v + w = 1 (barycentric coordinates).
  //
  // Substitution leads to an equation with 3 unknowns (e.g. t, u and v),
  // which can be solved using Cramer's rule:
  // t = det|O-C, A-C, B-C| / det|-d, A-C, B-C|
  // u = det| -d, O-C, B-C| / det|-d, A-C, B-C|
  // v = det| -d, A-C, O-C| / det|-d, A-C, B-C|
  //
  // In vector algebra the scalar triple product a * (b x c) can also
  // be understood as the determinant of the corresponding 3x3 matrix.

  V3 d  = ray.direction;
  V3 oc = ray.origin - c_;
  V3 ac = a_ - c_;
  V3 bc = b_ - c_;

  double det = ScalarTripleProduct(-d, ac, bc);
  // Check if ray and triangle are parallel.
  if (fabs(det) < EPS) return false;

  double t = ScalarTripleProduct(oc, ac, bc) / det;
  double u = ScalarTripleProduct(-d, oc, bc) / det;
  double v = ScalarTripleProduct(-d, ac, oc) / det;

  // Check if intersection point lies within the triangle.
  if (u < 0 || u > 1 || v < 0 || v > 1 || u + v > 1)
    return false;

  // Check if intersection point lies within the ray interval.
  if (t < ray.t_min || t > ray.t_max)
    return false;

  hit->distance = t;
  hit->material = material_;
  hit->position = ray.origin + t * ray.direction;
  hit->normal   = Norm3(VectorProduct(ac, bc));
  return true;
}
