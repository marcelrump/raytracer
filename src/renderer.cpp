// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "renderer.h"

Renderer::Renderer(const Camera &camera, const Scene &scene)
 : camera_(camera), scene_(scene)
{
  std::random_device rd;
  rng_ = std::mt19937(rd());
}

V3 Renderer::Radiance(const Ray &ray, int depth)
{
  Hit hit = scene_.Intersect(ray);
  return hit.material.color;
}

V3 Renderer::Render(const V2i &pixel)
{
  V3 color = {};
  for (int i = 0; i < samples_; i++)
  {
    Ray ray = camera_.CreateRay(pixel, rng_);
    color += Radiance(ray, 0);
  }
  return color / (double)samples_;
}
