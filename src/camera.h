// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_CAMERA_H_
#define RAYTRACER_SRC_CAMERA_H_

#include <random>

#include "basis3.h"
#include "ray.h"
#include "types.h"
#include "vector2.h"
#include "vector3.h"

class Camera
{
  // 3-dim. orthonormal basis
  // (Camera faces in negative z-direction
  //  to preserve the right-handedness of the system.)
  B3 onb3_;
  V3 eye_;
  int width_, height_;
  double aspect_ratio_;
  double horizontal_fov_;
  double camera_plane_distance_;
  double aperture_ = 0.;
  double focal_length_ = 1.;

 public:
  Camera(int width, int height,
         const V3 &eye,
         const V3 &orientation,
         const V3 &up = {0., 1., 0.},
         double view_angle = 120.);

  // NOTE(marcel): Supports only <std::mt19937> for now.
  template <typename RNG = std::mt19937>
  Ray CreateRay(const V2i &pixel, RNG &rng) const;

  void SetFocus(double aperture, double focal_length);
};

#endif // RAYTRACER_SRC_CAMERA_H_
