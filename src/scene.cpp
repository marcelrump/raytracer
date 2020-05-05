// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "scene.h"

#include "math.h"

Ray Scene::CreateShadowRay(const V3 &origin) const
{
  // Note(marcel): For the time being,
  // there is only one single point-like light source.
  V3 light = {0., 75., -75.};
  V3 l = light - origin;
  
  return Ray{origin, Norm3(l), EPS, Length(l) - EPS};
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
