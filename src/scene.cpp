// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "scene.h"

#include "math.h"

template<>
Ray Scene::CreateShadowRay<std::mt19937>(const V3 &origin,
                                         std::mt19937 &rng) const
{
  std::uniform_real_distribution<> r(-1., 1.);
  
  // Note(marcel): For the time being there is only one light source.
  V3 light = {20. * r(rng), 99.9, 20. * r(rng) - 75.};

  V3 l = light - origin;
  return Ray{origin, Norm3(l), EPS, Length(l)};
}

Hit Scene::Intersect(const Ray &ray) const
{
  Hit closest = {};
  Hit hit = {};

  for (const auto &primitive : primitives_)
  {
    if (primitive->Intersect(ray, &hit) &&
        hit.distance < closest.distance)
    {
      closest = hit;
    }
  }

  return closest;
}
