// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_RENDERER_H_
#define RAYTRACER_SRC_RENDERER_H_

#include <random>

#include "camera.h"
#include "ray.h"
#include "scene.h"
#include "types.h"
#include "vector2.h"
#include "vector3.h"

class Renderer
{
  const Camera &camera_;
  const Scene &scene_;
  std::mt19937 rng_;
  int samples_  = 4;
  int max_depth = 4;

 public:
  Renderer(const Camera &camera, const Scene &scene);
  V3 Render(const V2i &pixel);

 private:
  V3 Radiance(const Ray &ray, int depth);
};

#endif // RAYTRACER_SRC_RENDERER_H_
