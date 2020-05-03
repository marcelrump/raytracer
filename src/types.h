// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_TYPES_H_
#define RAYTRACER_SRC_TYPES_H_

#include <cstdint>

#include "basis3.h"
#include "vector2.h"
#include "vector3.h"

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef Basis3<double> B3;
typedef Basis3<int>    B3i;
typedef Basis3<float>  B3f;
typedef Basis3<double> B3d;

typedef Vector2<double> V2;
typedef Vector2<int>    V2i;
typedef Vector2<float>  V2f;
typedef Vector2<double> V2d;

typedef Vector3<double> V3;
typedef Vector3<int>    V3i;
typedef Vector3<float>  V3f;
typedef Vector3<double> V3d;

#endif // RAYTRACER_SRC_TYPES_H_
