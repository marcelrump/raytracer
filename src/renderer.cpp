// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#include "renderer.h"

#include <cmath>
#include <utility>

Renderer::Renderer(const Camera &camera, const Scene &scene)
 : camera_(camera), scene_(scene)
{
  std::random_device rd;
  rng_ = std::mt19937(rd());
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

// TODO(marcel): Maybe implement a background color.
V3 Renderer::Radiance(const Ray &ray, int depth)
{
  // End recursive part of the algorithm after a certain number of iterations.
  if (depth > max_depth) return Color{0., 0., 0.};

  // Check if something was hit.
  Hit hit = scene_.Intersect(ray);
  if (hit.distance == INF) return Color{0., 0., 0.};

  // V3 color = {};
  V3 color = hit.material.color * hit.material.ambient;

  // Adjust the normal orientation
  if (hit.normal * ray.direction > 0) hit.normal *= -1.;

  if (hit.material.type == DIFFUSE_AND_GLOSSY)
  {
    // Check if the object lies in shadow.
    // TODO(marcel): This should be sampled at some point.
    Ray shadow_ray = scene_.CreateShadowRay(hit.position);
    Hit obstacle = scene_.Intersect(shadow_ray);
    
    if (obstacle.distance == INF)
    {
      // Add a diffuse component
      color += hit.material.color * hit.material.diffuse
                                  * fabs(hit.normal * shadow_ray.direction);

      // Add a specular component
      V3 light_color = {1., 1., 1.};
      V3 h = Norm3(shadow_ray.direction - ray.direction);
      color += light_color * hit.material.specular
                           * pow(fabs(hit.normal * h), hit.material.glossiness);
    }
  }
  
  if (hit.material.type == REFLECTION_AND_REFRACTION)
  {
    
  }

  // NOTE(marcel): Purely reflective objects are handled as perfect mirrors.
  if (hit.material.type == REFLECTION_ONLY)
  {
    Ray reflected_ray = {};
    reflected_ray.origin = hit.position;
    reflected_ray.direction = Norm3(ray.direction + 2. * hit.normal
                                                       * fabs(hit.normal * ray.direction));                                                       
    
    V3 reflection = Radiance(reflected_ray, depth + 1);
    color += reflection;
  }

  return color;
}
