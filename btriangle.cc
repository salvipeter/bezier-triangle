#include <cmath>
#include <map>
#include <stdexcept>

#include "btriangle.hh"

using Point = BTriangle::Point;
using Mesh = BTriangle::Mesh;

Point::Point(double x, double y, double z) : data{x, y, z}
{
}

double
Point::operator[](size_t i) const {
  return data[i];
}

Point
Point::operator*(double x) const {
  return {data[0] * x, data[1] * x, data[2] * x};
}

void
Point::operator+=(const Point &p) {
  data[0] += p.data[0];
  data[1] += p.data[1];
  data[2] += p.data[2];
}

BTriangle::BTriangle(size_t degree, std::vector<Point> cp) : degree(degree), cp(cp)
{
  if (cp.size() != (degree + 1) * (degree + 2) / 2)
    throw std::invalid_argument("wrong number of control points");
}

namespace {

  size_t factorial(size_t n) {
    static std::map<size_t, size_t> cache;
    if (n == 0)
      return 1;
    if (auto x = cache.find(n); x != cache.end())
      return x->second;
    return cache[n] = n * factorial(n - 1);
  }

  double bernstein(size_t n, size_t i, size_t j, size_t k, const Point &p) {
    // Warning: this can only be used for small degrees
    size_t trinomial = factorial(n) / (factorial(i) * factorial(j) * factorial(k));
    return (double)trinomial * std::pow(p[0], i) * std::pow(p[1], j) * std::pow(p[2], k);
  }

}

Point
BTriangle::eval(const Point &p) const {
  Point result;

  size_t index = 0;
  for (size_t i = 0; i <= degree; ++i)
    for (size_t j = 0; j <= degree - i; ++j, ++index) {
      size_t k = degree - i - j;
      result += cp[index] * bernstein(degree, i, j, k, p);
    }

  return result;
}

Mesh
BTriangle::evalMesh(size_t resolution) const {
  Mesh m;
  for (size_t i = 0; i <= resolution; ++i) {
    double u = (double)i / resolution;
    for (size_t j = 0; j <= resolution - i; ++j) {
      double v = (double)j / resolution;
      double w = 1.0 - u - v;
      m.points.emplace_back(eval({u, v, w}));
    }
  }
  size_t index = 0;
  for (size_t i = 0; i < resolution; ++i, ++index)
    for (size_t j = 0; j < resolution - i; ++j, ++index) {
      size_t next = index + resolution - i;
      m.triangles.push_back({index, index + 1, next + 1});
      if (j != 0)
        m.triangles.push_back({index, next + 1, next});
    }
  return m;
}

