// Author: Marcel Rump
// E-Mail: rumpmarcel@gmail.com

#ifndef RAYTRACER_SRC_VECTOR2_H_
#define RAYTRACER_SRC_VECTOR2_H_

#include <cmath>

// Template representing 2-dimensional vectors.
template <typename T>
struct Vector2
{
  T x, y;
};

template <typename T>
inline Vector2<T> operator+(const Vector2<T> &u,
                            const Vector2<T> &v)
{
  return {u.x + v.x,
          u.y + v.y};
}

template <typename T>
inline Vector2<T> &operator+=(Vector2<T> &u, const Vector2<T> &v)
{
  u.x += v.x;
  u.y += v.y;
}

template <typename T>
inline Vector2<T> operator-(const Vector2<T> &u,
                            const Vector2<T> &v)
{
  return {u.x - v.x,
          u.y - v.y};
}

template <typename T>
inline Vector2<T> &operator-=(Vector2<T> &u, const Vector2<T> &v)
{
  u.x -= v.x;
  u.y -= v.y;
}

template <typename T>
inline T operator*(const Vector2<T> &u, const Vector2<T> &v)
{
  return u.x * v.x + u.y * v.y;
}

template <typename T>
inline Vector2<T> operator*(const Vector2<T> &v, T a)
{
  return {v.x * a,
          v.y * a};
}

template <typename T>
inline Vector2<T> operator*(T a, const Vector2<T> &v)
{
  return v * a;
}

template <typename T>
inline Vector2<T> &operator*=(Vector2<T> &v, T a)
{
  v.x *= a;
  v.y *= a;
}

template <typename T>
inline Vector2<T> operator/(const Vector2<T> &v, T a)
{
  return {v.x / a,
          v.y / a};
}

template <typename T>
inline Vector2<T> &operator/=(Vector2<T> &v, T a)
{
  v.x /= a;
  v.y /= a;
}

template <typename T>
inline Vector2<T> operator-(const Vector2<T> &v)
{
  return {-v.x, -v.y};
}

template <typename T>
inline bool operator==(const Vector2<T> &u,
                       const Vector2<T> &v)
{
  return u.x == v.x &&
         u.y == v.y;
}

template <typename T>
inline bool operator!=(const Vector2<T> &u,
                       const Vector2<T> &v)
{
  return u.x != v.x ||
         u.y != v.y;
}

template <typename T>
inline T Length(const Vector2<T> &v)
{
  return sqrt(v * v);
}

template <typename T>
inline T LengthSquared(const Vector2<T> &v)
{
  return v * v;
}

template <typename T>
inline Vector2<T> Norm2(const Vector2<T> &v)
{
  return v / Length(v);
}

#endif // RAYTRACER_SRC_VECTOR2_H_
