// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

// C system headers
// (more precisely: headers in angle brackets with the .h extension), e.g. <unistd.h>, <stdlib.h>.

// C++ standard library headers
// (without file extension), e.g. <algorithm>, <cstddef>.
#include <memory>

// Other libraries' headers

// Project headers
#include "camera.h"
#include "types.h"
#include "vector3.h"

// int main(int argc, const char * argv[])
int main()
{
  int width = 1920;
  int height = 1080;

  // Allocate memory for the image
  V3 * memory = (V3 *)malloc(sizeof(V3) * width * height);

  Camera camera(width, height, {0., 50., 0.}, {0., -0.0, -1.});
  // camera.SetFocus(0.01, 3.);
}
