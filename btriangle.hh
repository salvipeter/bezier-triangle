#pragma once

#include <array>
#include <vector>

class BTriangle {
public:
  struct Point {
    double data[3];
    Point(double x = 0.0, double y = 0.0, double z = 0.0);
    double operator[](size_t i) const;
    Point operator*(double x) const;
    void operator+=(const Point &p);
  };
  struct Mesh {
    using Triangle = std::array<size_t, 3>;
    std::vector<Point> points;
    std::vector<Triangle> triangles;
  };

  BTriangle(size_t degree, std::vector<Point> cp);
  Point eval(const Point &p) const;
  Mesh evalMesh(size_t resolution) const;
  
private:
  size_t degree;
  std::vector<Point> cp;
};
