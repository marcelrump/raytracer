// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "scene.h"

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
