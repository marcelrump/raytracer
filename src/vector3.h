// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_VECTOR3_H_
#define RAYTRACER_SRC_VECTOR3_H_

#include <cmath>

// Template representing 3-dimensional vectors.
template <typename T>
union Vector3
{
  struct
  {
    T x, y, z;
  };
  struct
  {
    T r, g, b;
  };
};

template <typename T>
inline Vector3<T> operator+(const Vector3<T> &u,
                            const Vector3<T> &v)
{
  return {u.x + v.x,
          u.y + v.y,
          u.z + v.z};
}

template <typename T>
inline Vector3<T> &operator+=(Vector3<T> &u, const Vector3<T> &v)
{
  u.x += v.x;
  u.y += v.y;
  u.z += v.z;
}

template <typename T>
inline Vector3<T> operator-(const Vector3<T> &u,
                            const Vector3<T> &v)
{
  return {u.x - v.x,
          u.y - v.y,
          u.z - v.z};
}

template <typename T>
inline Vector3<T> &operator-=(Vector3<T> &u, const Vector3<T> &v)
{
  u.x -= v.x;
  u.y -= v.y;
  u.z -= v.z;
}

template <typename T>
inline T operator*(const Vector3<T> &u,
                   const Vector3<T> &v)
{
  return u.x * v.x +
         u.y * v.y +
         u.z * v.z;
}

template <typename T>
inline Vector3<T> operator*(T a, const Vector3<T> &v)
{
  return {v.x * a,
          v.y * a,
          v.z * a};
}

template <typename T>
inline Vector3<T> operator*(const Vector3<T> &v, T a)
{
  return {v.x * a,
          v.y * a,
          v.z * a};
}

template <typename T>
inline Vector3<T> &operator*=(Vector3<T> &v, T a)
{
  v.x *= a;
  v.y *= a;
  v.z *= a;
}

template <typename T>
inline Vector3<T> operator/(const Vector3<T> &v, T a)
{
  return {v.x / a,
          v.y / a,
          v.z / a};
}

template <typename T>
inline Vector3<T> &operator/=(Vector3<T> &v, T a)
{
  v.x /= a;
  v.y /= a;
  v.z /= a;
}

template <typename T>
inline Vector3<T> operator-(const Vector3<T> &v)
{
  return {-v.x, -v.y, -v.z};
}

template <typename T>
inline bool operator==(const Vector3<T> &u,
                       const Vector3<T> &v)
{
  return u.x == v.x &&
         u.y == v.y &&
         u.z == v.z;
}

template <typename T>
inline bool operator!=(const Vector3<T> &u,
                       const Vector3<T> &v)
{
  return u.x != v.x ||
         u.y != v.y ||
         u.z != v.z;
}

template <typename T>
inline T Length(const Vector3<T> &v)
{
  return sqrt(v * v);
}

template <typename T>
inline T LengthSquared(const Vector3<T> &v)
{
  return v * v;
}

template <typename T>
inline Vector3<T> Norm3(const Vector3<T> &v)
{
  return v / Length(v);
}

template <typename T>
inline Vector3<T> VectorProduct(const Vector3<T> &u,
                                const Vector3<T> &v)
{
  return {u.y * v.z - u.z * v.y,
          u.z * v.x - u.x * v.z,
          u.x * v.y - u.y * v.x};
}

template <typename T>
inline T ScalarTripleProduct(const Vector3<T> &u,
                             const Vector3<T> &v,
                             const Vector3<T> &w)
{
  return u * VectorProduct(v, w);
}

#endif // RAYTRACER_SRC_VECTOR3_H_
