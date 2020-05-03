// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "camera.h"

#include <cassert>

#include "math.h"

Camera::Camera(int width, int height,
               const V3 &eye,
               const V3 &orientation,
               const V3 &up,
               double horizontal_fov)
 : width_(width), height_(height),
   aspect_ratio_(static_cast<double>(width) / height),
   eye_(eye), horizontal_fov_(horizontal_fov)
{
  // Camera must not be pointed directly upwards.
  assert(VectorProduct(up, orientation) != V3(0., 0., 0.));

  // Check view angle
  assert(horizontal_fov > 0. && horizontal_fov < 180.);

  camera_plane_distance_ = 1. / tan(horizontal_fov / 360. * PI);

  onb3_.x_axis = Norm3(VectorProduct(up, -orientation));
  onb3_.y_axis = Norm3(VectorProduct(onb3_.x_axis, orientation));
  onb3_.z_axis = Norm3(-orientation);
}

template<>
Ray Camera::CreateRay<std::mt19937>(const V2i &pixel,
                                    std::mt19937 &rng) const
{
  assert(pixel.x >= 0 && pixel.x < width_);
  assert(pixel.y >= 0 && pixel.y < height_);

  std::uniform_real_distribution<> pixel_offset(0., 1.);

  double x = (1. - 2. * ((double)pixel.x + pixel_offset(rng)) / width_);
  double y = (1. - 2. * ((double)pixel.y + pixel_offset(rng)) / height_);

  V3 vx =  onb3_.x_axis * x;
  V3 vy =  onb3_.y_axis * y / aspect_ratio_;
  V3 vz = -onb3_.z_axis * camera_plane_distance_;

  V3 direction = Norm3(vx + vy + vz);

  if (aperture_ == 0)
    return Ray{eye_, direction, 0, INF};

  V3 focal_point = eye_ + direction * focal_length_; 

  std::uniform_real_distribution<> angular_distribution(0., 2. * PI);
  std::uniform_real_distribution<> radial_distribution(0., aperture_);

  double angle = angular_distribution(rng);
  double radius = radial_distribution(rng);

  V3 origin = eye_ + (onb3_.x_axis * cos(angle) * radius)
                   + (onb3_.y_axis * sin(angle) * radius);

  return Ray{origin, Norm3(focal_point - origin), 0, INF};
}

void Camera::SetFocus(double aperture, double focal_length)
{
  assert(aperture >= 0 && focal_length > 0);
  aperture_ = aperture;
  focal_length = focal_length;
}
