// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

// C system headers
// (more precisely: headers in angle brackets with the .h extension), e.g. <unistd.h>, <stdlib.h>.
#include <omp.h>

// C++ standard library headers
// (without file extension), e.g. <algorithm>, <cstddef>.
#include <memory>

// Other libraries' headers

// Project headers
#include "camera.h"
#include "material.h"
#include "plane.h"
#include "renderer.h"
#include "scene.h"
#include "sphere.h"
#include "triangle.h"
#include "types.h"
#include "vector3.h"

// int main(int argc, const char * argv[])
int main()
{
  int width = 1920;
  int height = 1080;

  // Allocate memory for the image
  V3 * memory = (V3 *)malloc(sizeof(V3) * width * height);

  Camera camera(width, height, {0., 50., 0.}, {0., -0.04, -1.});
  // camera.SetFocus(0.01, 3.);

  Scene scene;
  scene.Add(Plane({   0.,   0.,    0.}, {0., 1., 0.}, Material{Color{0.75, 0.75, 0.75}}));
  scene.Add(Plane({   0., 100.,    0.}, {0., 1., 0.}, Material{Color{0.75, 0.75, 0.75}}));
  scene.Add(Plane({-100.,   0.,    0.}, {1., 0., 0.}, Material{Color{0.75, 0.25, 0.25}}));
  scene.Add(Plane({ 100.,   0.,    0.}, {1., 0., 0.}, Material{Color{0.25, 0.75, 0.25}}));
  scene.Add(Plane({   0.,   0.,  150.}, {0., 0., 1.}, Material{Color{0.75, 0.75, 0.75}}));
  scene.Add(Plane({   0.,   0., -150.}, {0., 0., 1.}, Material{Color{0.75, 0.75, 0.75}}));
  scene.Add(Sphere(20., {-20., 20.,  -97.}, Material{Color{0., 1., 1.}}));
  scene.Add(Sphere(20., { 50., 20., -128.}, Material{Color{0., 0., 0.}, REFLECTION_ONLY}));
  scene.Add(Triangle({-100., 50., -150.}, {0., 0., -150.}, {-100., 0., -100.}, Material{Color{1., 1., 1.}}));

  Renderer renderer(camera, scene);
  
  #pragma omp parallel for
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      memory[y * width + x] = renderer.Render({x, y});
    }
  }

  FILE * image;
  image = fopen("image.ppm", "wb");
  fprintf(image, "P3\n%d %d\n%d\n", width, height, 255); 
  for (int i = 0; i < width * height; i++)
  {
    fprintf(image,"%d %d %d ", int(clamp(memory[i].r) * 255),
                               int(clamp(memory[i].g) * 255),
                               int(clamp(memory[i].b) * 255));
  } 
  fclose(image);
}
