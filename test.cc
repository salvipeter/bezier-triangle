#include <fstream>

#include "btriangle.hh"

int main(int argc, char **argv) {
  BTriangle bt(3, {{1,1,0},{3,1,1},{5,1,1},{7,1,0},
                      {2,3,1},{4,3,3},{6,3,1},
                         {3,5,1},{5,5,1},
                            {4,7,0}});
  auto mesh = bt.evalMesh(30);

  std::ofstream f("test.obj");
  for (const auto &p : mesh.points)
    f << "v " << p[0] << ' ' << p[1] << ' ' << p[2] << std::endl;
  for (const auto &t : mesh.triangles)
    f << "f " << t[0] + 1 << ' ' << t[1] + 1 << ' ' << t[2] + 1 << std::endl;

  return 0;
}
