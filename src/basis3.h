// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_BASIS3_H_
#define RAYTRACER_SRC_BASIS3_H_

#include "vector3.h"

// Template representing a basis of a 3-dimensional vector space.
template <typename T>
struct Basis3
{
  Vector3<T> x_axis;
  Vector3<T> y_axis;
  Vector3<T> z_axis;
};

#endif // RAYTRACER_SRC_BASIS_H_
