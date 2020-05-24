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
  // Check if something was hit.
  Hit hit = scene_.Intersect(ray);
  if (hit.distance == INF) return Color{0., 0., 0.};

  // End recursive part of the algorithm after a certain number of iterations.
  if (depth > max_depth) return hit.material.emission;

  // Do not reflect off of light sources
  if (hit.material.emission != V3{0., 0., 0.}) return hit.material.emission;  

  V3 color = hit.material.emission;
  if (hit.material.type == DIFFUSE_AND_GLOSSY)
  {
    V3 n = hit.normal;
    V3 r = Norm3(ray.direction);

    if (n * r > 0) n *= -1.;

    // Create orthonormal basis
    B3 onb3;
    if (VectorProduct(n, {1., 0., 0.}) != V3(0., 0., 0.))
      onb3.x_axis = Norm3(VectorProduct(n, {1., 0., 0.}));
    else
      onb3.x_axis = Norm3(VectorProduct(n, {0., 1., 0.}));
    onb3.y_axis = Norm3(VectorProduct(onb3.x_axis, n));
    onb3.z_axis = Norm3(n);

    std::uniform_real_distribution<> unit(0., 1.);
    double phi = 2. * PI * unit(rng_);
    double theta = PI / 2. * unit(rng_);

    V3 d = onb3.x_axis * sin(theta) * cos(phi)
         + onb3.y_axis * sin(theta) * sin(phi)
         + onb3.z_axis * cos(theta);

    Ray diffuse_ray = {hit.position, d};
    color += Multiply(hit.material.color, Radiance(diffuse_ray, depth + 1));
  }

  // NOTE(marcel): Purely reflective objects are handled as perfect mirrors.
  if (hit.material.type == REFLECTIVE)
  {
    V3 r = Norm3(ray.direction);
    V3 n = Norm3(hit.normal);

    Ray reflected_ray = {};
    reflected_ray.origin = hit.position;
    reflected_ray.direction = r + 2. * n * fabs(n * r);
    
    color += Radiance(reflected_ray, depth + 1);
  }

    
  // NOTE(marcel): For now, reflection and refraction is only handled
  // correctly for spheres, since that makes it easier to identify
  // transitions between refractive indices.
  if (hit.material.type == REFLECTIVE_AND_REFRACTIVE)
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
    reflected_ray.direction = r + 2. * n * fabs(r * n);
    
    color += R * Radiance(reflected_ray, depth + 1);
  }

  return color;
}
