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

  // Evaluate the Phong illumination model in case of diffuse and/or glossy objects.
  if (hit.material.type == DIFFUSE_AND_GLOSSY)
  {
    // Check if the object lies in shadow.
    // TODO(marcel): This should be sampled at some point.
    Ray shadow_ray = scene_.CreateShadowRay(hit.position);
    Hit obstacle = scene_.Intersect(shadow_ray);
    
    if (obstacle.distance == INF)
    {
      double d = hit.material.diffuse;
      double s = hit.material.specular;
      double g = hit.material.glossiness;
      V3 c = hit.material.color;
      V3 n = hit.normal;
      V3 l = Norm3(shadow_ray.direction);
      V3 r = Norm3(ray.direction);
      V3 h = Norm3(l - r);

      // Add a diffuse component
      color += c * d * fabs(n * l);

      // Add a specular component
      V3 light_color = {1., 1., 1.};
      color += light_color * s * pow(fabs(n * h), g);
    }
  }
  
  // NOTE(marcel): For now, reflection and refraction is only handled
  // correctly for spheres, since that makes it easier to identify
  // transitions between refractive indices.
  if (hit.material.type == REFLECTION_AND_REFRACTION)
  {
    double eta_i = 1.5;
    double eta_o = 1.0;

    V3 r = Norm3(ray.direction);
    V3 n = hit.normal;

    // Check which side the ray comes from and adjust both normal
    // as well as refractive indices accordingly.
    double cos_theta = n * r;
    if (cos_theta > 0)
    {
      std::swap(eta_i, eta_o);
      n *= -1.;
    }
    else
    {
      cos_theta *= -1.;
    }

    // Calculate the Fresnel factor using Schlick's approximation.
    double R_0 = pow((eta_i - eta_o) / (eta_i + eta_o), 2.);
    double R = R_0 + (1. - R_0) * pow(1. - cos_theta, 5.);
    double T = 1. - R;
 
    V3 v = r / cos_theta;
    double k = pow(eta_i / eta_o, 2.) * LengthSquared(v) - LengthSquared(v + n);

    // If not total internal reflection, then cast refracted ray.
    if (k < 0)
    {
      R = 1.;
      T = 0.;
    }
    else
    {
      double kf = 1 / sqrt(k);

      Ray refracted_ray = {};
      refracted_ray.origin = hit.position;
      refracted_ray.direction = kf * (n + v) - n;

      color += T * Radiance(refracted_ray, depth + 1);
    }

    Ray reflected_ray = {};
    reflected_ray.origin = hit.position;
    reflected_ray.direction = Norm3(r + 2. * n);
    
    color += R * Radiance(reflected_ray, depth + 1);
  }

  // NOTE(marcel): Purely reflective objects are handled as perfect mirrors.
  if (hit.material.type == REFLECTION_ONLY)
  {
    V3 r = Norm3(ray.direction);
    V3 n = hit.normal;

    Ray reflected_ray = {};
    reflected_ray.origin = hit.position;
    reflected_ray.direction = Norm3(r + 2. * n);
    
    color += Radiance(reflected_ray, depth + 1);
  }

  return color;
}
