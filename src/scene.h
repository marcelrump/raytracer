// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_SCENE_H_
#define RAYTRACER_SRC_SCENE_H_

#include <memory>
#include <vector>

#include "hit.h"
#include "primitive.h"
#include "ray.h"

class Scene
{
  std::vector<std::unique_ptr<Primitive>> primitives_;

 public:
  Scene() = default;

  template <typename T>
  void Add(const T &primitive)
  {
    primitives_.emplace_back(std::make_unique<T>(primitive));
  }

  Hit Intersect(const Ray &ray) const;
};

#endif // RAYTRACER_SRC_SCENE_H_
